/*
 * Copyright 2014 Google Inc. All rights reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <cstdio>

#include <map>
#include <memory>
#include <string>
#include <vector>

#include <curl/curl.h>

using ::std::string;

typedef struct {
  string in_source_url;
  string in_href_url;
  string out_source_page;
} LinkTestData;

size_t WriteData(void *buffer, size_t size, size_t nmemb, void *userp) {
  LinkTestData *link_test_data = (LinkTestData *)userp;
  char *body = (char *)buffer;
  link_test_data->out_source_page.append(body, body + nmemb);
  return size * nmemb;
}

static string HtmlEntityEncode(const string &s) {
  string escaped;
  static const std::map<char, string> entity_of{
    {'&', "&amp;"},
    {'<', "&lt;"},
    {'>', "&gt;"},
    {'"', "&quot;"},
    {'\'', "&#x27;"},
    {'/', "&#x2F;"},
  };
  for (char c : s) {
    if (entity_of.count(c) == 1) {
      escaped.append(entity_of.at(c));
    } else {
      escaped.push_back(c);
    }
  }
  return escaped;
}

int main(int argc, char **argv) {
  using std::vector;

  curl_global_init(CURL_GLOBAL_ALL);
  CURL *handle = curl_easy_init();

  std::unique_ptr<char[]> buf(new char[1000]);
  char *page_buf = NULL;
  size_t page_len = 0;
  long num_links = 0;
  long num_links_broken = 0;
  while (true) {
    int status = scanf("%999s", buf.get());
    if (status == EOF) {
      break;
    }
    string source(buf.get());
    scanf("%999s", buf.get());
    string href(buf.get());
    LinkTestData link = {source, href, {}};

    curl_easy_setopt(handle, CURLOPT_URL, source.c_str());
    curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, WriteData);
    curl_easy_setopt(handle, CURLOPT_WRITEDATA, &link);
    CURLcode success = curl_easy_perform(handle);

    ++num_links;
    if (link.out_source_page.find(href) != string::npos) {
      ++num_links_broken;
    } else {
      printf(
          "<li>%s→%s</li>\n",
          HtmlEntityEncode(source).c_str(),
          HtmlEntityEncode(href).c_str());
    }
  }
  printf("%lu/%lu broken links still present\n", num_links_broken, num_links);

  curl_easy_cleanup(handle);
  curl_global_cleanup();
  return 0;
}

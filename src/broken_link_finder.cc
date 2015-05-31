#include <cstdio>

#include <string>
#include <vector>

#include <curl/curl.h>

using std::vector;
using std::string;

struct LinkTestData {
  string in_source_url;
  string in_href_url;
  string out_source_page;
};

size_t WriteData(void *buffer, size_t size, size_t nmemb, void *userp) {
  LinkTestData *link_test_data = (LinkTestData *)userp;
  char *body = (char *)buffer;
  link_test_data->out_source_page.append(body, body + nmemb);
  return size * nmemb;
}

int main(int argc, char *argv[]) {
  string root(argv[1]);

  printf("%s\n", root.c_str());

  curl_global_init(CURL_GLOBAL_ALL);
  CURL *handle = curl_easy_init();

  LinkTestData link = {};
  
  curl_easy_setopt(handle, CURLOPT_URL, root.c_str());
  curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, WriteData);
  curl_easy_setopt(handle, CURLOPT_WRITEDATA, &link);
  CURLcode success = curl_easy_perform(handle);

  printf("%s\n", link.out_source_page.c_str());

  curl_easy_cleanup(handle);
  curl_global_cleanup();

  return 0;
}

#include <stdio.h>
#include <unistd.h>

#include <memory>
#include <string>
#include <vector>

#include <curl/curl.h>

typedef struct {
  std::string in_source_url;
  std::string in_href_url;
  std::string out_source_page;
} LinkTestData;

size_t WriteData(void *buffer, size_t size, size_t nmemb, void *userp) {
  LinkTestData *link_test_data = (LinkTestData *)userp;
  // printf("%s %s\n", link->source.c_str(), link->href.c_str());
  char *body = (char *)buffer;
  link_test_data->out_source_page.append(body, body + nmemb);
  return size * nmemb;
}

int main(int argc, char **argv) {
  using std::string;
  using std::vector;

  curl_global_init(CURL_GLOBAL_ALL);
  CURL *handle = curl_easy_init();

  std::unique_ptr<char[]> buf(new char[1000]);
  char *page_buf = NULL;
  size_t page_len = 0;
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
    printf("%s\n", link.out_source_page.c_str());
    sleep(1);
  }

  curl_easy_cleanup(handle);
  curl_global_cleanup();
  return 0;
}
#ifndef JSON_FRM_PARSE_H
#define JSON_FRM_PARSE_H
 
#ifdef __cplusplus
extern "C" {
#endif

int login_json_to_str_parse(const char *jsonFrm, const char *buf);
int recv_json_to_str_parse(const char *jsonFrm, const char *buf);
int request_result_parse(const char *json_result, char *dataKey);

#ifdef __cplusplus
}
#endif
#endif
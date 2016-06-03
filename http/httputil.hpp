/* 
 * File:   httputil.h
 * Author: 
 *
 * Created on 
 */

#ifndef HTTPUTIL_H
#define	HTTPUTIL_H

#ifdef	__cplusplus
extern "C" {
#endif

#define HTTP_POST_PARA_LENGTH	2048
#define HTTP_POST_URL_LENGTH	2048


int isFileExist(char * savePath);
int download(char *uri, char *savePath) ;

int netGet(char* url, char* params, int timeout, char *result, int *result_len) ;
int netPost(char* uri, char* params, int timeout, char *result, int *result_len) ;

#ifdef	__cplusplus
}
#endif

#endif	/* HTTPUTIL_H */


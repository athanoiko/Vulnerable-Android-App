#include "nativelib.h"

extern "C"
JNIEXPORT jstring JNICALL
Java_com_oiko_vulnerableapp_MainActivity_stringFromJNI(JNIEnv *env, jobject thiz) {
    std::string hello = "Hello from native world!";
    return env->NewStringUTF(hello.c_str());
}

extern "C"
JNIEXPORT jstring JNICALL
Java_com_oiko_vulnerableapp_MainActivity_crash(JNIEnv *env, jobject thiz) {
    char buf[1];
    char * src = "crash";
    strncpy(buf, src, sizeof(src));
}

extern "C"
JNIEXPORT void JNICALL
Java_com_oiko_vulnerableapp_MainActivity_stackBufferUnderflow(JNIEnv *env, jobject thiz, jstring param) {
    char buf[12];
    const char * input= (*env).GetStringUTFChars(param, NULL);
    strncpy(buf, input, sizeof(buf));
    size_t length = strlen(buf);
    int index = (length - 1);
    while (buf[index] != ':') {
        buf[index] = '\0';
        index--;
    }
}

extern "C"
JNIEXPORT void JNICALL
Java_com_oiko_vulnerableapp_MainActivity_stackBufferOverflow(JNIEnv *env, jobject thiz, jstring param) {
    char buf[5];
    const char * input= (*env).GetStringUTFChars(param, NULL);
    strcpy(buf, input);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_oiko_vulnerableapp_MainActivity_heapBufferOverflow(JNIEnv *env, jobject thiz, jstring param) {
    int BUFSIZE = 10;
    char * buf = static_cast<char *>(malloc(sizeof(char) * BUFSIZE));
    const char * input= (*env).GetStringUTFChars(param, NULL);
    strcpy(buf, input);
    free(buf);
}
extern "C"
JNIEXPORT void JNICALL
Java_com_oiko_vulnerableapp_MainActivity_useAfterFree(JNIEnv *env, jobject thiz, jstring param) {
    int BUFSIZE = 10;
    char * buf = static_cast<char *>(malloc(sizeof(char) * BUFSIZE));
    const char * input= (*env).GetStringUTFChars(param, NULL);
    strncpy(buf, input, strlen(input));
    free(buf);
    strncpy(buf, input, strlen(input));
}

extern "C"
JNIEXPORT void JNICALL
Java_com_oiko_vulnerableapp_MainActivity_numericTruncation(JNIEnv *env, jobject thiz) {
    unsigned int buf1_len = UINT_MAX - 256;
    unsigned int buf2_len = 256;
    unsigned int buf3_len = 256;

    char buf1[buf1_len], buf2[buf2_len], buf3[buf3_len];
    int buf3_new_len = (buf1_len + buf2_len);

    if (buf3_new_len <= 256) {
        memcpy(buf3, buf1, buf1_len);
        memcpy(buf3 + buf1_len, buf2, buf2_len);
    }
}

extern "C"
JNIEXPORT jint JNICALL
Java_com_oiko_vulnerableapp_MainActivity_fuzzTest1(JNIEnv *env, jobject thiz, jstring param, jint len) {
    char local_buf[15];
    const char * buf= (*env).GetStringUTFChars(param, NULL);
    if (len > 0 && buf[0] == 'H')
        if (len > 1 && buf[1] == 'I')
            if (len > 2 && buf[2] == '!')
                return 1;
    return 0;
}

int char_test(char a){
    if (a == 'a') {
        return 1;
    } else {
        if (a == 'I') {
            return 0;
        }
        return 8;
    }
}

extern "C"
JNIEXPORT jint JNICALL
Java_com_oiko_vulnerableapp_MainActivity_fuzzTest2(JNIEnv *env, jobject thiz, jstring param, jint len) {
    char local_buf[15];
    const char * buf= (*env).GetStringUTFChars(param, NULL);
    if (strlen(buf) == 4564) return 2;

    if (strlen(buf) == 3 && buf[5] == 'B') return 1;

    if (buf[5] == 'C') return 1;

    if (strlen(buf) > 0 && buf[0] == 'X' && buf[1] == 'd') {
        memcpy(local_buf+16, buf, strlen(buf));
    }

    if (char_test('u') > 1) {
        return 4;
    };

    return 1;
}
extern "C"
JNIEXPORT jint JNICALL
Java_com_oiko_vulnerableapp_MainActivity_fuzzTest3(JNIEnv *env, jobject thiz, jstring param, jint len) {
    char local_buf[2];
    const char * buf= (*env).GetStringUTFChars(param, NULL);
    if (len > 0 && buf[0] == 'H')
        if (len > 1 && buf[1] == 'I')
            if (len > 2 && buf[2] == '!')
                memcpy(local_buf, buf, strlen(buf));
    return 0;
}

extern "C"
void c_fuzz_test_2(char *buf, int len) {
    char local_buf[13];
    if (strlen(buf) == 4564) return;

    if (strlen(buf) == 3 && buf[5] == 'B') return;

    if (buf[5] == 'C') return;

    if (strlen(buf) > 0 && buf[0] == 'X' && buf[1] == 'd') {
        memcpy(local_buf+16, buf, strlen(buf));
    }

    if (char_test('u') > 1) {
        return;
    };
}

extern "C"
int c_fuzz_test_1(char *buf, int len) {
    char local_buf[2];
    if (len > 0 && buf[0] == 'H')
        if (len > 1 && buf[1] == 'I')
            if (len > 2 && buf[2] == '!')
                memcpy(local_buf, buf, strlen(buf));
    return 0;
}

extern "C"
int c_fuzz_test_3(char *buf, int len) {
    char local_buf[2];
    if (len > 0 && buf[0] == 'H')
        if (len > 1 && buf[1] == 'I' && char_test(buf[1]) == 0)
            if (len > 2 && buf[2] == '!')
                memcpy(local_buf, buf, strlen(buf));
    return 0;
}
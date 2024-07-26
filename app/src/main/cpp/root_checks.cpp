#include <jni.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdio.h>

extern "C" {

// Check for SU binary
JNIEXPORT jboolean JNICALL
Java_com_utils_rootdetection_utils_RootUtil_checkForSU(JNIEnv *env, jobject thiz) {
    if (access("/system/xbin/su", F_OK) != -1 || access("/system/bin/su", F_OK) != -1) {
        return JNI_TRUE;
    } else {
        return JNI_FALSE;
    }
}

// Example of a native method to check writable paths (a direct translation of checkForRWPaths)
JNIEXPORT jboolean JNICALL
Java_com_utils_rootdetection_utils_RootUtil_checkForWritablePaths(JNIEnv *env, jobject thiz) {
    const char* paths[] = {
            "/system",
            "/system/bin",
            "/system/sbin",
            "/system/xbin",
            "/vendor/bin",
            "/sbin",
            "/etc",
            // Add more paths here as needed
    };
    int pathsLength = sizeof(paths) / sizeof(paths[0]);

    for (int i = 0; i < pathsLength; ++i) {
        const char* path = paths[i];
        // Attempting to write a temporary file to the path
        char tmpFilePath[PATH_MAX];
        snprintf(tmpFilePath, sizeof(tmpFilePath), "%s/tmp.txt", path);
        FILE* tmpFile = fopen(tmpFilePath, "w");
        if (tmpFile != NULL) {
            fclose(tmpFile);
            remove(tmpFilePath); // Clean up
            return JNI_TRUE; // Writable path found
        }
    }
    return JNI_FALSE; // No writable paths found
}

}
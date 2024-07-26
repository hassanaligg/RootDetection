package com.utils.rootdetection.utils

import android.content.Context


object RootUtil {

    init {
        System.loadLibrary("root_checks")
    }

    external fun checkForSU(): Boolean
    external fun checkForWritablePaths(): Boolean

    fun isDeviceRooted(context: Context): Boolean {
        // Integrate native methods with your existing logic
        return checkForSU() || checkForWritablePaths() || checkRootManagementApps(context)
    // Add your other checks as needed
    }
    private fun checkRootManagementApps(context: Context): Boolean {
        val packages = arrayOf(
            "com.noshufou.android.su",
            "eu.chainfire.supersu",
            "com.koushikdutta.superuser",
            "com.thirdparty.superuser",
            "com.yellowes.su",
            "com.frida.android",
            "com.koushikdutta.superuser",
            "com.topjohnwu.magisk",
            "com.kingroot.kinguser",
            "com.android.settings.development",
            "com.cydia",
            "com.saurik.substrate",
            "com.rootchecker",
            "com.devadvance.rootcloak2",
            "com.zachspong.temprootremovejb",
            "com.jrummyapps.rootchecker",
            "de.robv.android.xposed.installer",
            "com.schiztech.batteryfu",
            "com.ramdroid.appquarantine",
            "com.ramdroid.appguard",
        )
        return packages.any { isPackageInstalled(it,context) }
    }
    private fun isPackageInstalled(packageName: String, context: Context): Boolean {
        val pm = context.packageManager
        return try {
            pm.getPackageInfo(packageName, 0)
            true
        } catch (e: Exception) {
            false
        }
    }
}


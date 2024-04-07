package me.bzcoder.fixandroid14debuggablelag

import com.bytedance.shadowhook.ShadowHook
import com.bytedance.shadowhook.ShadowHook.ConfigBuilder


class FixTools{


    external fun fixAndroid14DebuggableLag()

    companion object {
        // Used to load the 'fixandroid14debuggablelag' library on application startup.
        init {
            System.loadLibrary("fixandroid14debuggablelag")

            ShadowHook.init(
                ConfigBuilder()
                    .setMode(ShadowHook.Mode.UNIQUE)
                    .build()
            )
        }
    }
}
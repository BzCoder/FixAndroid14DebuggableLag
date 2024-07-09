# 一行代码修复Android 14 Debug下卡顿问题
[![](https://jitpack.io/v/BzCoder/FixAndroid14DebuggableLag.svg)](https://jitpack.io/#BzCoder/FixAndroid14DebuggableLag)

在启动时添加以下代码：

```kotlin

 FixTools().fixAndroid14DebuggableLag()

```
 
```gradle
dependencyResolutionManagement {
    repositoriesMode.set(RepositoriesMode.FAIL_ON_PROJECT_REPOS)
    repositories {
        mavenCentral()
        maven { url 'https://jitpack.io' }
    }
}


```
 
```gradle

dependencies {
    implementation 'com.github.BzCoder:FixAndroid14DebuggableLag:1.0.0'
}

```



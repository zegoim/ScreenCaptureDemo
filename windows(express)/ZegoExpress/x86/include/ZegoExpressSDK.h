
#ifndef __ZEGOEXPRESSSDK_H__
#define __ZEGOEXPRESSSDK_H__

#include "internal/ZegoInternalEngineImpl.hpp"

namespace ZEGO {
namespace EXPRESS {

class ZegoExpressSDK {
  private:
    ZegoExpressSDK() = default;
    ~ZegoExpressSDK() = default;

  public:
    /// Create ZegoExpressEngine singleton object and initialize SDK.
    ///
    /// Available since: 2.14.0
    /// Description: Create ZegoExpressEngine singleton object and initialize SDK.
    /// When to call: The engine needs to be created before calling other functions.
    /// Restrictions: None.
    /// Caution: The SDK only supports the creation of one instance of ZegoExpressEngine. Multiple calls to this function return the same object.
    ///
    /// @param profile The basic configuration information is used to create the engine.
    /// @param eventHandler Event notification callback. [nullptr] means not receiving any callback notifications.It can also be managed later via [setEventHandler]. If [createEngine] is called repeatedly and the [destroyEngine] function is not called to destroy the engine before the second call, the eventHandler will not be updated.
    /// @return engine singleton instance.
    static IZegoExpressEngine *createEngine(ZegoEngineProfile profile,
                                            std::shared_ptr<IZegoEventHandler> eventHandler) {
        return ZegoExpressSDKInternal::createEngine(profile, eventHandler);
    }

    /// Destroy the ZegoExpressEngine singleton object and deinitialize the SDK.
    ///
    /// Available since: 1.1.0
    /// Description: Destroy the ZegoExpressEngine singleton object and deinitialize the SDK.
    /// When to call: When the SDK is no longer used, the resources used by the SDK can be released through this interface
    /// Restrictions: None.
    /// Caution: After using [createEngine] to create a singleton, if the singleton object has not been created or has been destroyed, you will not receive related callbacks when calling this function.
    ///
    /// @param engine engine instance that created by createEngine method.
    /// @param callback Notification callback for destroy engine completion. Developers can listen to this callback to ensure that device hardware resources are released. If the developer only uses SDK to implement audio and video functions, this parameter can be passed [nullptr].
    static void destroyEngine(IZegoExpressEngine *&engine,
                              ZegoDestroyCompletionCallback callback = nullptr) {
        ZegoExpressSDKInternal::destroyEngine(engine, callback);
    }

    /// Returns the singleton instance of ZegoExpressEngine.
    ///
    /// Available since: 1.1.0
    /// Description: If the engine has not been created or has been destroyed, returns [nullptr].
    /// When to call: After creating the engine, before destroying the engine.
    /// Restrictions: None.
    ///
    /// @return Engine singleton instance
    static IZegoExpressEngine *getEngine() { return ZegoExpressSDKInternal::getEngine(); }

    /// Set advanced engine configuration.
    ///
    /// Available since: 1.1.0
    /// Description: Used to enable advanced functions.
    /// When to call: Different configurations have different call timing requirements. For details, please consult ZEGO technical support.
    /// Restrictions: None.
    ///
    /// @param config Advanced engine configuration
    static void setEngineConfig(ZegoEngineConfig config) {
        ZegoExpressSDKInternal::setEngineConfig(config);
    }

    /// Set log configuration.
    ///
    /// Available since: 2.3.0
    /// Description: If you need to customize the log file size and path, please call this function to complete the configuration.
    /// When to call: It must be set before calling [createEngine] to take effect. If it is set after [createEngine], it will take effect at the next [createEngine] after [destroyEngine].
    /// Restrictions: None.
    /// Caution: Once this interface is called, the method of setting log size and path via [setEngineConfig] will be invalid.Therefore, it is not recommended to use [setEngineConfig] to set the log size and path.
    ///
    /// @param config log configuration.
    static void setLogConfig(ZegoLogConfig config) { ZegoExpressSDKInternal::setLogConfig(config); }

    /// Set room mode.
    ///
    /// Available since: 2.9.0
    /// Description: If you need to use the multi-room feature, please call this function to complete the configuration.
    /// When to call: Must be set before calling [createEngine] to take effect, otherwise it will fail.
    /// Restrictions: If you need to use the multi-room feature, please contact the instant technical support to configure the server support.
    /// Caution: None.
    ///
    /// @param mode Room mode. Description: Used to set the room mode. Use cases: If you need to enter multiple rooms at the same time for publish-play stream, please turn on the multi-room mode through this interface. Required: True. Default value: ZEGO_ROOM_MODE_SINGLE_ROOM.
    static void setRoomMode(ZegoRoomMode mode) { ZegoExpressSDKInternal::setRoomMode(mode); }

    /// Gets the SDK's version number.
    ///
    /// Available since: 1.1.0
    /// Description: If you encounter an abnormality during the running of the SDK, you can submit the problem, log and other information to the ZEGO technical staff to locate and troubleshoot. Developers can also collect current SDK version information through this API, which is convenient for App operation statistics and related issues.
    /// When to call: Any time.
    /// Restrictions: None.
    /// Caution: None.
    ///
    /// @return SDK version.
    static std::string getVersion() { return ZegoExpressSDKInternal::getVersion(); }

    /// Sets the JVM and Context for the Android platform.
    ///
    /// Available since: 1.1.0
    /// Description: Sets the JVM and Context for the Android platform.
    /// When to call: It must be called before calling [createEngine] function.
    /// Restrictions: Only available on Android platform.
    /// Caution: None.
    ///
    /// @param jvm Java VM Object.
    /// @param context Android Context, it must be valid in the SDK lifecycle.
    static void setAndroidEnv(void *jvm, void *context) {
        ZegoExpressSDKInternal::setAndroidEnv(jvm, context);
    }

    /// Set method execution result callback.
    ///
    /// Available since: 2.3.0
    /// Description: Set the setting of the execution result of the calling method. After setting, you can get the detailed information of the result of each execution of the ZEGO SDK method.
    /// When to call: Any time.
    /// Restrictions: None.
    /// Caution: It is recommended that developers call this interface only when they need to obtain the call results of each interface. For example, when troubleshooting and tracing problems. Developers generally do not need to pay attention to this interface.
    ///
    /// @param callback Method execution result callback.
    static void setApiCalledCallback(std::shared_ptr<IZegoApiCalledEventHandler> callback) {
        ZegoExpressSDKInternal::setApiCalledCallback(callback);
    }

    /// [Deprecated] Create ZegoExpressEngine singleton object and initialize SDK.
    ///
    /// Available: 1.1.0 ~ 2.13.1, deprecated since 2.14.0, please use the method with the same name without [isTestEnv] parameter instead
    /// Description: Create ZegoExpressEngine singleton object and initialize SDK.
    /// When to call: The engine needs to be created before calling other functions.
    /// Restrictions: None.
    /// Caution: The SDK only supports the creation of one instance of ZegoExpressEngine. Multiple calls to this function return the same object.
    ///
    /// @deprecated Deprecated since 2.14.0, please use the method with the same name without [isTestEnv] parameter instead.
    /// @param appID Application ID issued by ZEGO for developers, please apply from the ZEGO Admin Console https://console.zegocloud.com The value ranges from 0 to 4294967295.
    /// @param appSign Application signature for each AppID, please apply from the ZEGO Admin Console. Application signature is a 64 character string. Each character has a range of '0' ~ '9', 'a' ~ 'z'. AppSign 2.17.0 and later allows nullptr or no transmission. If the token is passed empty or not passed, the token must be entered in the [ZegoRoomConfig] parameter for authentication when the [loginRoom] interface is called to login to the room.
    /// @param isTestEnv Choose to use a test environment or a formal commercial environment, the formal environment needs to submit work order configuration in the ZEGO management console. The test environment is for test development, with a limit of 10 rooms and 50 users. Official environment App is officially launched. ZEGO will provide corresponding server resources according to the configuration records submitted by the developer in the management console. The test environment and the official environment are two sets of environments and cannot be interconnected.
    /// @param scenario The application scenario. Developers can choose one of ZegoScenario based on the scenario of the app they are developing, and the engine will preset a more general setting for specific scenarios based on the set scenario. After setting specific scenarios, developers can still call specific functions to set specific parameters if they have customized parameter settings.
    /// @param eventHandler Event notification callback. [nullptr] means not receiving any callback notifications.It can also be managed later via [setEventHandler]. If [createEngine] is called repeatedly and the [destroyEngine] function is not called to destroy the engine before the second call, the eventHandler will not be updated.
    /// @return Engine singleton instance.
    ZEGO_DEPRECATED
    static IZegoExpressEngine *createEngine(unsigned int appID, const std::string &appSign,
                                            bool isTestEnv, ZegoScenario scenario,
                                            std::shared_ptr<IZegoEventHandler> eventHandler) {
        return ZegoExpressSDKInternal::createEngine(appID, appSign, isTestEnv, scenario,
                                                    eventHandler);
    }
};

} //namespace EXPRESS
} //namespace ZEGO

#endif //__ZEGOEXPRESSSDK_H__

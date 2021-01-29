//
//  Version: 2.1.0.563_stable_video_whiteboard
//
//  Copyright © 2019 Zego. All rights reserved.
//

#ifndef __ZEGOEXPRESSSDK_H__
#define __ZEGOEXPRESSSDK_H__

#include "internal/ZegoInternalEngineImpl.hpp"

namespace ZEGO {
    namespace EXPRESS {

        class ZegoExpressSDK
        {
        private:
            ZegoExpressSDK() = default;
            ~ZegoExpressSDK() = default;
        public:

            /**
             * Creates a singleton instance of ZegoExpressEngine.
             *
             * The engine needs to be created and initialized before calling other functions. The SDK only supports the creation of one instance of ZegoExpressEngine. Multiple calls to this function return the same object.
             *
             * @param appID Application ID issued by ZEGO for developers, please apply from the ZEGO Admin Console https://console-express.zego.im The value ranges from 0 to 4294967295.
             * @param appSign Application signature for each AppID, please apply from the ZEGO Admin Console. Application signature is a 64 character string. Each character has a range of '0' ~ '9', 'a' ~ 'z'.
             * @param isTestEnv Choose to use a test environment or a formal commercial environment, the formal environment needs to submit work order configuration in the ZEGO management console. The test environment is for test development, with a limit of 10 rooms and 50 users. Official environment App is officially launched. ZEGO will provide corresponding server resources according to the configuration records submitted by the developer in the management console. The test environment and the official environment are two sets of environments and cannot be interconnected.
             * @param scenario The application scenario. Developers can choose one of ZegoScenario based on the scenario of the app they are developing, and the engine will preset a more general setting for specific scenarios based on the set scenario. After setting specific scenarios, developers can still call specific functions to set specific parameters if they have customized parameter settings.
             * @param eventHandler Event notification callback. [nullptr] means not receiving any callback notifications.It can also be managed later via [setEventHandler]
             * @return Engine singleton instance.
             */
            static IZegoExpressEngine* createEngine(unsigned int appID, const std::string& appSign, bool isTestEnv, ZegoScenario scenario, std::shared_ptr<IZegoEventHandler> eventHandler) {
                return ZegoExpressSDKInternal::createEngine(appID, appSign, isTestEnv, scenario, eventHandler);
            }

            /**
             * Destroys the singleton instance of ZegoExpressEngine asynchronously.
             *
             * Used to release resources used by ZegoExpressEngine.
             *
             * @param engine engine instance that created by createEngine method
             * @param callback Notification callback for destroy engine completion. Developers can listen to this callback to ensure that device hardware resources are released. This callback is only used to notify the completion of the release of internal resources of the engine. Developers cannot release resources related to the engine within this callback. If the developer only uses SDK to implement audio and video functions, this parameter can be passed [nullptr].
             */
            static void destroyEngine(IZegoExpressEngine*& engine, ZegoDestroyCompletionCallback callback = nullptr) {
                ZegoExpressSDKInternal::destroyEngine(engine, callback);
            }

            /**
             * Returns the singleton instance of ZegoExpressEngine.
             *
             * If the engine has not been created or has been destroyed, returns [nullptr].
             *
             * @return Engine singleton instance
             */
            static IZegoExpressEngine* getEngine() {
                return ZegoExpressSDKInternal::getEngine();
            }

            /**
             * Set advanced engine configuration.
             *
             * Developers need to call this function to set advanced function configuration when they need advanced functions of the engine.
             *
             * @param config Advanced engine configuration
             */
            static void setEngineConfig(ZegoEngineConfig config) {
                ZegoExpressSDKInternal::setEngineConfig(config);
            }

            /**
             * Gets the SDK's version number.
             *
             * When the SDK is running, the developer finds that it does not match the expected situation and submits the problem and related logs to the ZEGO technical staff for locating. The ZEGO technical staff may need the information of the engine version to assist in locating the problem.
             * Developers can also collect this information as the version information of the engine used by the app, so that the SDK corresponding to each version of the app on the line.
             *
             * @return SDK version
             */
            static std::string getVersion() {
                return ZegoExpressSDKInternal::getVersion();
            }

            /**
             * Sets the JVM and Context for the Android platform. It must be called before calling [createEngine] on the Android platform.
             *
             * @param jvm Java VM Object
             * @param context Android Context, it must be valid in the SDK lifecycle.
             */
            static void setAndroidEnv(void* jvm, void* context) {
                ZegoExpressSDKInternal::setAndroidEnv(jvm, context);
            }

        };

    } //namespace EXPRESS
} //namespace ZEGO

#endif //__ZEGOEXPRESSSDK_H__

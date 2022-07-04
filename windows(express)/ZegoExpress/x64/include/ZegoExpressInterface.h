﻿
#ifndef __ZEGOEXPRESSINTERFACE_H__
#define __ZEGOEXPRESSINTERFACE_H__

#include "ZegoExpressDefines.h"
#include "ZegoExpressErrorCode.h"
#include "ZegoExpressEventHandler.h"

namespace ZEGO {
namespace EXPRESS {

class IZegoMediaPlayer;
class IZegoAudioEffectPlayer;
class IZegoRangeAudio;
class IZegoRealTimeSequentialDataManager;
class IZegoMediaDataPublisher;

class IZegoExpressEngine {
  protected:
    virtual ~IZegoExpressEngine() {}

  public:
    /// Sets up the event notification callbacks that need to be handled. If the eventHandler is set to [nullptr], all the callbacks set previously will be cleared.
    ///
    /// Available since: 1.1.0
    /// Description: Set up event notification callbacks, used to monitor callbacks such as engine status changes, room status changes, etc.
    /// When to call: After [createEngine].
    /// Restrictions: None.
    /// Caution: Invoke this function will overwrite the handler set in [createEngine] or the handler set by the last call to this method. After calling [destroyEngine], the event handler that has been set will be invalid and need to be reset after next calling of [createEngine].
    ///
    /// @param eventHandler Event notification callback. If the eventHandler is set to [nullptr], all the callbacks set previously will be cleared. Developers should monitor the corresponding callbacks according to their own business scenarios. The main callback functions of the SDK are here.
    virtual void setEventHandler(std::shared_ptr<IZegoEventHandler> eventHandler) = 0;

    /// Uploads logs to the ZEGO server.
    ///
    /// Available since: 1.1.0
    /// Description: By default, SDK creates and prints log files in the App's default directory. Each log file defaults to a maximum of 5MB. Three log files are written over and over in a circular fashion. When calling this function, SDK will auto package and upload the log files to the ZEGO server.
    /// Use cases: Developers can provide a business “feedback” channel in the App. When users feedback problems, they can call this function to upload the local log information of SDK to help locate user problems.
    /// When to call: After [createEngine].
    /// Restrictions: If you call this interface repeatedly within 10 minutes, only the last call will take effect.
    /// Caution: After calling this interface to upload logs, if you call [destroyEngine] or exit the App too quickly, there may be a failure.It is recommended to wait a few seconds, and then call [destroyEngine] or exit the App after receiving the upload success callback.
    virtual void uploadLog() = 0;

    /// Uploads logs to the ZEGO server.
    ///
    /// Available since: 2.4.0
    /// Description: By default, SDK creates and prints log files in the App's default directory. Each log file defaults to a maximum of 5MB. Three log files are written over and over in a circular fashion. When calling this function, SDK will auto package and upload the log files to the ZEGO server.
    /// Use cases: Developers can provide a business “feedback” channel in the App. When users feedback problems, they can call this function to upload the local log information of SDK to help locate user problems.
    /// When to call: After [createEngine].
    /// Restrictions: If you call this interface repeatedly within 10 minutes, only the last call will take effect.
    /// Caution: After calling this interface to upload logs, if you call [destroyEngine] or exit the App too quickly, there may be a failure.It is recommended to wait a few seconds, and then call [destroyEngine] or exit the App after receiving the upload success callback..
    ///
    /// @param callback Log upload result callback.
    virtual void uploadLog(ZegoUploadLogResultCallback callback) = 0;

    /// Enable the debugg assistant. Note, do not enable this feature in the online version! Use only during development phase!
    ///
    /// Available since: 2.17.0
    /// Description: After enabled, the SDK will print logs to the console, and will pop-up an alert (toast) UI message when there is a problem with calling other SDK functions.
    /// Default value: This function is disabled by default.
    /// When to call: This function can be called right after [createEngine].
    /// Platform differences: The pop-up alert function only supports Android / iOS / macOS / Windows, and the console log function supports all platforms.
    /// Caution: Be sure to confirm that this feature is turned off before the app is released to avoid pop-up UI alert when an error occurs in your release version's app. It is recommended to associate the [enable] parameter of this function with the DEBUG variable of the app, that is, only enable the debugg assistant in the DEBUG environment.
    /// Restrictions: None.
    ///
    /// @param enable Whether to enable the debugg assistant.
    virtual void enableDebugAssistant(bool enable) = 0;

    /// Call the RTC experimental API.
    ///
    /// Available since: 2.7.0
    /// Description: ZEGO provides some technical previews or special customization functions in RTC business through this API. If you need to get the use of the function or the details, please consult ZEGO technical support.
    /// When to call: After [createEngine].
    ///
    /// @param params You need to pass in a parameter in the form of a JSON string, please consult ZEGO technical support for details.
    /// @return Returns an argument in the format of a JSON string, please consult ZEGO technical support for details.
    virtual std::string callExperimentalAPI(const std::string &params) = 0;

    /// Set the path of the static picture would be published when the camera is closed.
    ///
    /// Available: since 2.9.0
    /// Description: Set the path of the static picture would be published when enableCamera(false) is called, it would start to publish static pictures, and when enableCamera(true) is called, it would end publishing static pictures.
    /// Use case: The developer wants to display a static picture when the camera is closed. For example, when the anchor exits the background, the camera would be actively closed. At this time, the audience side needs to display the image of the anchor temporarily leaving.
    /// When to call: After the engine is initialized, call this API to configure the parameters before closing the camera.
    /// Restrictions:
    ///   1. Supported picture types are JPEG/JPG, PNG, BMP, HEIF.
    ///   2. The function is only for SDK video capture and does not take effect for custom video capture.
    ///   3. Not supported that the filePath is a network link.
    /// Caution:
    ///   1. The static picture cannot be seen in the local preview.
    ///   2. External filters, mirroring, watermarks, and snapshots are all invalid.
    ///   3. If the picture aspect ratio is inconsistent with the set code aspect ratio, it will be cropped according to the code aspect ratio.
    /// Platform differences:
    ///   1. Windows: Fill in the location of the picture directly, such as "D://dir//image.jpg".
    ///   2. iOS: If it is a full path, add the prefix "file:", such as @"file:/var/image.png"; If it is a assets picture path, add the prefix "asset:", such as @"asset:watermark".
    ///   3. Android: If it is a full path, add the prefix "file:", such as "file:/sdcard/image.png"; If it is a assets directory path, add the prefix "asset:", such as "asset:watermark.png".
    ///
    /// @param filePath Picture file path
    /// @param channel Publish channel.
    virtual void
    setDummyCaptureImagePath(const std::string &filePath,
                             ZegoPublishChannel channel = ZEGO_PUBLISH_CHANNEL_MAIN) = 0;

    /// Logs in to a room. You must log in to a room before publishing or playing streams.
    ///
    /// Available since: 1.1.0
    /// Description: SDK uses the 'room' to organize users. After users log in to a room, they can use interface such as push stream [startPublishingStream], pull stream [startPlayingStream], send and receive broadcast messages [sendBroadcastMessage], etc.
    /// Use cases: In the same room, users can conduct live broadcast, audio and video calls, etc.
    /// When to call /Trigger: This interface is called after [createEngine] initializes the SDK.
    /// Restrictions: For restrictions on the use of this function, please refer to https://docs.zegocloud.com/article/7611 or contact ZEGO technical support.
    /// Caution:
    ///   1. Apps that use different appIDs cannot intercommunication with each other.
    ///   2. SDK supports startPlayingStream audio and video streams from different rooms under the same appID, that is, startPlayingStream audio and video streams across rooms. Since ZegoExpressEngine's room related callback notifications are based on the same room, when developers want to startPlayingStream streams across rooms, developers need to maintain related messages and signaling notifications by themselves.
    ///   3. It is strongly recommended that userID corresponds to the user ID of the business APP, that is, a userID and a real user are fixed and unique, and should not be passed to the SDK in a random userID. Because the unique and fixed userID allows ZEGO technicians to quickly locate online problems.
    ///   4. After the first login failure due to network reasons or the room is disconnected, the default time of SDK reconnection is 20min.
    ///   5. After the user has successfully logged in to the room, if the application exits abnormally, after restarting the application, the developer needs to call the logoutRoom interface to log out of the room, and then call the loginRoom interface to log in to the room again.
    /// Privacy reminder: Please do not fill in sensitive user information in this interface, including but not limited to mobile phone number, ID number, passport number, real name, etc.
    /// Related callbacks:
    ///   1. When the user starts to log in to the room, the room is successfully logged in, or the room fails to log in, the [onRoomStateChanged] (Not supported before 2.18.0, please use [onRoomStateUpdate]) callback will be triggered to notify the developer of the status of the current user connected to the room.
    ///   2. Different users who log in to the same room can get room related notifications in the same room (eg [onRoomUserUpdate], [onRoomStreamUpdate], etc.), and users in one room cannot receive room signaling notifications in another room.
    ///   3. If the network is temporarily interrupted due to network quality reasons, the SDK will automatically reconnect internally. You can get the current connection status of the local room by listening to the [onRoomStateChanged] (Not supported before 2.18.0, please use [onRoomStateUpdate]) callback method, and other users in the same room will receive [onRoomUserUpdate] callback notification.
    ///   4. Messages sent in one room (e.g. [setStreamExtraInfo], [sendBroadcastMessage], [sendBarrageMessage], [sendCustomCommand], etc.) cannot be received callback ((eg [onRoomStreamExtraInfoUpdate], [onIMRecvBroadcastMessage], [onIMRecvBarrageMessage], [onIMRecvCustomCommand], etc) in other rooms. Currently, SDK does not provide the ability to send messages across rooms. Developers can integrate the SDK of third-party IM to achieve.
    /// Related APIs:
    ///   1. Users can call [logoutRoom] to log out. In the case that a user has successfully logged in and has not logged out, if the login interface is called again, the console will report an error and print the error code 1002001.
    ///   2. SDK supports multi-room login, please call [setRoomMode] function to select multi-room mode before engine initialization, and then call [loginRoom] to log in to multi-room.
    ///   3. Calling [destroyEngine] will also automatically log out.
    ///
    /// @param roomID Room ID, a string of up to 128 bytes in length. Only support numbers, English characters and '~', '!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '_', '+', '=', '-', '`', ';', '’', ',', '.', '<', '>', '/', '\'.
    /// @param user User object instance, configure userID, userName. Note that the userID needs to be globally unique with the same appID, otherwise the user who logs in later will kick out the user who logged in first.
    virtual void loginRoom(const std::string &roomID, ZegoUser user) = 0;

    /// Logs in to a room with advanced room configurations. You must log in to a room before publishing or playing streams.
    ///
    /// Available since: 1.1.0
    /// Description: SDK uses the 'room' to organize users. After users log in to a room, they can use interface such as push stream [startPublishingStream], pull stream [startPlayingStream], send and receive broadcast messages [sendBroadcastMessage], etc. To prevent the app from being impersonated by a malicious user, you can add authentication before logging in to the room, that is, the [token] parameter in the ZegoRoomConfig object passed in by the [config] parameter.
    /// Use cases: In the same room, users can conduct live broadcast, audio and video calls, etc.
    /// When to call /Trigger: This interface is called after [createEngine] initializes the SDK.
    /// Restrictions: For restrictions on the use of this function, please refer to https://docs.zegocloud.com/article/7611 or contact ZEGO technical support.
    /// Caution:
    ///   1. Apps that use different appIDs cannot intercommunication with each other.
    ///   2. SDK supports startPlayingStream audio and video streams from different rooms under the same appID, that is, startPlayingStream audio and video streams across rooms. Since ZegoExpressEngine's room related callback notifications are based on the same room, when developers want to startPlayingStream streams across rooms, developers need to maintain related messages and signaling notifications by themselves.
    ///   3. It is strongly recommended that userID corresponds to the user ID of the business APP, that is, a userID and a real user are fixed and unique, and should not be passed to the SDK in a random userID. Because the unique and fixed userID allows ZEGO technicians to quickly locate online problems.
    ///   4. After the first login failure due to network reasons or the room is disconnected, the default time of SDK reconnection is 20min.
    ///   5. After the user has successfully logged in to the room, if the application exits abnormally, after restarting the application, the developer needs to call the logoutRoom interface to log out of the room, and then call the loginRoom interface to log in to the room again.
    /// Privacy reminder: Please do not fill in sensitive user information in this interface, including but not limited to mobile phone number, ID number, passport number, real name, etc.
    /// Related callbacks:
    ///   1. When the user starts to log in to the room, the room is successfully logged in, or the room fails to log in, the [onRoomStateChanged] (Not supported before 2.18.0, please use [onRoomStateUpdate]) callback will be triggered to notify the developer of the status of the current user connected to the room.
    ///   2. Different users who log in to the same room can get room related notifications in the same room (eg [onRoomUserUpdate], [onRoomStreamUpdate], etc.), and users in one room cannot receive room signaling notifications in another room.
    ///   3. If the network is temporarily interrupted due to network quality reasons, the SDK will automatically reconnect internally. You can get the current connection status of the local room by listening to the [onRoomStateChanged] (Not supported before 2.18.0, please use [onRoomStateUpdate]) callback method, and other users in the same room will receive [onRoomUserUpdate] callback notification.
    ///   4. Messages sent in one room (e.g. [setStreamExtraInfo], [sendBroadcastMessage], [sendBarrageMessage], [sendCustomCommand], etc.) cannot be received callback ((eg [onRoomStreamExtraInfoUpdate], [onIMRecvBroadcastMessage], [onIMRecvBarrageMessage], [onIMRecvCustomCommand], etc) in other rooms. Currently, SDK does not provide the ability to send messages across rooms. Developers can integrate the SDK of third-party IM to achieve.
    /// Related APIs:
    ///   1. Users can call [logoutRoom] to log out. In the case that a user has successfully logged in and has not logged out, if the login interface is called again, the console will report an error and print the error code 1002001.
    ///   2. SDK supports multi-room login, please call [setRoomMode] function to select multi-room mode before engine initialization, and then call [loginRoom] to log in to multi-room.
    ///   3. Calling [destroyEngine] will also automatically log out.
    ///
    /// @param roomID Room ID, a string of up to 128 bytes in length. Only support numbers, English characters and '~', '!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '_', '+', '=', '-', '`', ';', '’', ',', '.', '<', '>', '/', '\'.
    /// @param user User object instance, configure userID, userName. Note that the userID needs to be globally unique with the same appID, otherwise the user who logs in later will kick out the user who logged in first.
    /// @param config Advanced room configuration.
    /// @param callback The callback of this login result(2.18.0 and above version support), if you need detailed room status, please pay attention to the [onRoomStateChanged] callback. Required: No. Default value: nullptr.Caution: If the connection is retried multiple times due to network problems, the retry status will not be thrown by this callback.
    virtual void loginRoom(const std::string &roomID, ZegoUser user, ZegoRoomConfig config,
                           ZegoRoomLoginCallback callback = nullptr) = 0;

    /// Logs out of a room.
    ///
    /// Available since: 2.9.0
    /// Description: This API will log out the current user has logged in the room, if user logs in more than one room, all the rooms will be logged out.
    /// Use cases: In the same room, users can conduct live broadcast, audio and video calls, etc.
    /// When to call /Trigger: After successfully logging in to the room, if the room is no longer used, the user can call the function [logoutRoom].
    /// Restrictions: None.
    /// Caution: 1. Exiting the room will stop all publishing and playing streams for user, and inner audio and video engine will stop, and then SDK will auto stop local preview UI. If you want to keep the preview ability when switching rooms, please use the [switchRoom] method. 2. If the user is not logged in to the room, calling this function will also return success.
    /// Related callbacks: After calling this function, you will receive [onRoomStateChanged] (Not supported before 2.18.0, please use [onRoomStateUpdate]) callback notification successfully exits the room, while other users in the same room will receive the [onRoomUserUpdate] callback notification(On the premise of enabling isUserStatusNotify configuration).
    /// Related APIs: Users can use [loginRoom], [switchRoom] functions to log in or switch rooms.
    ///
    /// @param callback The callback of this logout room result, if you need detailed room status, please pay attention to the [onRoomStateChanged] callback.. Required: No. Default value: nullptr.
    virtual void logoutRoom(ZegoRoomLogoutCallback callback = nullptr) = 0;

    /// Logs out of a room.
    ///
    /// Available since: 1.1.0
    /// Description: This API will log out the room named roomID.
    /// Use cases: In the same room, users can conduct live broadcast, audio and video calls, etc.
    /// When to call /Trigger: After successfully logging in to the room, if the room is no longer used, the user can call the function [logoutRoom].
    /// Restrictions: None.
    /// Caution: 1. Exiting the room will stop all publishing and playing streams for user, and inner audio and video engine will stop, and then SDK will auto stop local preview UI. If you want to keep the preview ability when switching rooms, please use the [switchRoom] method. 2. If the user logs in to the room, but the incoming 'roomID' is different from the logged-in room name, SDK will return failure.
    /// Related callbacks: After calling this function, you will receive [onRoomStateChanged] (Not supported before 2.18.0, please use [onRoomStateUpdate]) callback notification successfully exits the room, while other users in the same room will receive the [onRoomUserUpdate] callback notification(On the premise of enabling isUserStatusNotify configuration).
    /// Related APIs: Users can use [loginRoom], [switchRoom] functions to log in or switch rooms.
    ///
    /// @param roomID Room ID, a string of up to 128 bytes in length. Only support numbers, English characters and '~', '!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '_', '+', '=', '-', '`', ';', '’', ',', '.', '<', '>', '/', '\'.
    /// @param callback The callback of this logout room result, if you need detailed room status, please pay attention to the [onRoomStateChanged] callback.. Required: No. Default value: nullptr.
    virtual void logoutRoom(const std::string &roomID,
                            ZegoRoomLogoutCallback callback = nullptr) = 0;

    /// Switch the room with advanced room configurations.
    ///
    /// Available since: 1.15.0
    /// Description: Using this interface allows users to quickly switch from one room to another room.
    /// Use cases: if you need to quickly switch to the next room, you can call this function.
    /// When to call /Trigger: After successfully login room.
    /// Restrictions: None.
    /// Caution:
    ///   1. When this function is called, all streams currently publishing or playing will stop (but the local preview will not stop).
    ///   2. To prevent the app from being impersonated by a malicious user, you can add authentication before logging in to the room, that is, the [token] parameter in the ZegoRoomConfig object passed in by the [config] parameter. This parameter configuration affects the room to be switched over. 3. When the function [setRoomMode] is used to set ZegoRoomMode to ZEGO_ROOM_MODE_MULTI_ROOM, this function is not available.
    /// Privacy reminder: Please do not fill in sensitive user information in this interface, including but not limited to mobile phone number, ID number, passport number, real name, etc.
    /// Related callbacks: When the user call the [switchRoom] function, the [onRoomStateChanged] (Not supported before 2.18.0, please use [onRoomStateUpdate]) callback will be triggered to notify the developer of the status of the current user connected to the room.
    /// Related APIs: Users can use the [logoutRoom] function to log out of the room.
    ///
    /// @param fromRoomID Current roomID.
    /// @param toRoomID The next roomID.
    /// @param config Advanced room configuration.
    virtual void switchRoom(const std::string &fromRoomID, const std::string &toRoomID,
                            ZegoRoomConfig *config = nullptr) = 0;

    /// Renew token.
    ///
    /// Available since: 2.8.0
    /// Description: After the developer receives [onRoomTokenWillExpire], they can use this API to update the token to ensure that the subsequent RTC functions are normal.
    /// Use cases: Used when the token is about to expire.
    /// When to call /Trigger: After the developer receives [onRoomTokenWillExpire].
    /// Restrictions: None.
    /// Caution: The token contains important information such as the user's room permissions, publish stream permissions, and effective time, please refer to https://docs.zegocloud.com/article/11649.
    /// Related callbacks: None.
    /// Related APIs: None.
    ///
    /// @param roomID Room ID.
    /// @param token The token that needs to be renew.
    virtual void renewToken(const std::string &roomID, const std::string &token) = 0;

    /// Set room extra information.
    ///
    /// Available since: 1.13.0
    /// Description: The user can call this function to set the extra info of the room.
    /// Use cases: You can set some room-related business attributes, such as whether someone is Co-hosting.
    /// When to call /Trigger: After logging in the room successful.
    /// Restrictions: For restrictions on the use of this function, please refer to https://docs.zegocloud.com/article/7611 or contact ZEGO technical support.
    /// Caution: 'key' is non nullptr. The length of key and value is limited, please refer to Restrictions. The newly set key and value will overwrite the old setting.
    /// Related callbacks: Other users in the same room will be notified through the [onRoomExtraInfoUpdate] callback function.
    /// Related APIs: None.
    ///
    /// @param roomID Room ID.
    /// @param key key of the extra info.
    /// @param value value if the extra info.
    /// @param callback Callback for setting room extra information.
    virtual void setRoomExtraInfo(const std::string &roomID, const std::string &key,
                                  const std::string &value,
                                  ZegoRoomSetRoomExtraInfoCallback callback) = 0;

    /// Starts publishing a stream (for the specified channel). You can call this function to publish a second stream.
    ///
    /// Available since: 1.1.0
    /// Description: Users push their local audio and video streams to the ZEGO RTC server or CDN, and other users in the same room can pull the audio and video streams to watch through the `streamID` or CDN pull stream address.
    /// Use cases: It can be used to publish streams in real-time connecting wheat, live broadcast and other scenarios.
    /// When to call: After [loginRoom].
    /// Restrictions: None.
    /// Caution:
    ///   1. Before start to publish the stream, the user can choose to call [setVideoConfig] to set the relevant video parameters, and call [startPreview] to preview the video.
    ///   2. Other users in the same room can get the streamID by monitoring the [onRoomStreamUpdate] event callback after the local user publishing stream successfully.
    ///   3. In the case of poor network quality, user publish may be interrupted, and the SDK will attempt to reconnect. You can learn about the current state and error information of the stream published by monitoring the [onPublisherStateUpdate] event.
    ///
    /// @param streamID Stream ID, a string of up to 256 characters, needs to be globally unique within the entire AppID. If in the same AppID, different users publish each stream and the stream ID is the same, which will cause the user to publish the stream failure. You cannot include URL keywords, otherwise publishing stream and playing stream will fails. Only support numbers, English characters and '~', '!', '@', '$', '%', '^', '&', '*', '(', ')', '_', '+', '=', '-', '`', ';', '’', ',', '.', '<', '>', '/', '\'.
    /// @param channel Publish stream channel.
    virtual void startPublishingStream(const std::string &streamID,
                                       ZegoPublishChannel channel = ZEGO_PUBLISH_CHANNEL_MAIN) = 0;

    /// Starts publishing a stream. Support multi-room mode.
    ///
    /// Available since: 1.1.0
    /// Description: Users push their local audio and video streams to the ZEGO RTC server or CDN, and other users in the same room can pull the audio and video streams to watch through the `streamID` or CDN pull stream address.
    /// Use cases: It can be used to publish streams in real-time connecting wheat, live broadcast and other scenarios.
    /// When to call: After [loginRoom].
    /// Restrictions: None.
    /// Caution:
    ///   1. Before start to publish the stream, the user can choose to call [setVideoConfig] to set the relevant video parameters, and call [startPreview] to preview the video.
    ///   2. Other users in the same room can get the streamID by monitoring the [onRoomStreamUpdate] event callback after the local user publishing stream successfully.
    ///   3. In the case of poor network quality, user publish may be interrupted, and the SDK will attempt to reconnect. You can learn about the current state and error information of the stream published by monitoring the [onPublisherStateUpdate] event.
    ///   4. To call [SetRoomMode] function to select multiple rooms, the room ID must be specified explicitly.
    ///
    /// @param streamID Stream ID, a string of up to 256 characters, needs to be globally unique within the entire AppID. If in the same AppID, different users publish each stream and the stream ID is the same, which will cause the user to publish the stream failure. You cannot include URL keywords, otherwise publishing stream and playing stream will fails. Only support numbers, English characters and '~', '!', '@', '$', '%', '^', '&', '*', '(', ')', '_', '+', '=', '-', '`', ';', '’', ',', '.', '<', '>', '/', '\'.
    /// @param config Advanced publish configuration.
    /// @param channel Publish stream channel.
    virtual void startPublishingStream(const std::string &streamID, ZegoPublisherConfig config,
                                       ZegoPublishChannel channel = ZEGO_PUBLISH_CHANNEL_MAIN) = 0;

    /// Stops publishing a stream (for the specified channel).
    ///
    /// Available since: 1.1.0
    /// Description: The user stops sending local audio and video streams, and other users in the room will receive a stream deletion notification.
    /// Use cases: It can be used to stop publish streams in real-time connecting wheat, live broadcast and other scenarios.
    /// When to call: After [startPublishingStream].
    /// Restrictions: None.
    /// Caution:
    ///   1. After stopping the streaming, other users in the same room can receive the delete notification of the stream by listening to the [onRoomStreamUpdate] callback.
    ///   2. If the user has initiated publish flow, this function must be called to stop the publish of the current stream before publishing the new stream (new streamID), otherwise the new stream publish will return a failure.
    ///   3. After stopping streaming, the developer should stop the local preview based on whether the business situation requires it.
    ///
    /// @param channel Publish stream channel.
    virtual void stopPublishingStream(ZegoPublishChannel channel = ZEGO_PUBLISH_CHANNEL_MAIN) = 0;

    /// Sets the extra information of the stream being published for the specified publish channel.
    ///
    /// Available since: 1.1.0
    /// Description: Use this function to set the extra info of the stream. The stream extra information is an extra information identifier of the stream ID. Unlike the stream ID, which cannot be modified during the publishing process, the stream extra information can be modified midway through the stream corresponding to the stream ID. Developers can synchronize variable content related to stream IDs based on stream additional information.
    /// When to call: After the engine is created [createEngine], Called before and after [startPublishingStream] can both take effect.
    /// Restrictions: None.
    /// Related callbacks: Users can obtain the execution result of the function through [ZegoPublisherSetStreamExtraInfoCallback] callback.
    ///
    /// @param extraInfo Stream extra information, a string of up to 1024 characters.
    /// @param callback Set stream extra information execution result notification.
    /// @param channel Publish stream channel.
    virtual void setStreamExtraInfo(const std::string &extraInfo,
                                    ZegoPublisherSetStreamExtraInfoCallback callback,
                                    ZegoPublishChannel channel = ZEGO_PUBLISH_CHANNEL_MAIN) = 0;

    /// Starts/Updates the local video preview (for the specified channel).
    ///
    /// Available since: 1.1.0
    /// Description: The user can see his own local image by calling this function.
    /// Use cases: It can be used for local preview in real-time connecting wheat, live broadcast and other scenarios.
    /// When to call: After [createEngine].
    /// Restrictions: None.
    /// Caution: 1. The preview function does not require you to log in to the room or publish the stream first. But after exiting the room, SDK internally actively stops previewing by default. 2. Local view and preview modes can be updated by calling this function again. The user can only preview on one view. If you call [startPreview] again to pass in a new view, the preview screen will only be displayed in the new view. 3. You can set the mirror mode of the preview by calling the [setVideoMirrorMode] function. The default preview setting is image mirrored. 4. When this function is called, the audio and video engine module inside SDK will start really, and it will start to try to collect audio and video..
    /// Note: This function is only available in ZegoExpressVideo SDK!
    ///
    /// @param canvas The view used to display the preview image. If the view is set to nullptr, no preview will be made.
    /// @param channel Publish stream channel
    virtual void startPreview(ZegoCanvas *canvas,
                              ZegoPublishChannel channel = ZEGO_PUBLISH_CHANNEL_MAIN) = 0;

    /// Starts the local audio preview.
    ///
    /// Available since: 1.1.0
    /// Description: Call this function after creating the engine and before publishing/playing a stream, and then the engine will start to capture audio.
    /// Use cases: Can check whether the audio equipment works ok by calling this function and by the soundlevel function of Engine.
    /// When to call: After [createEngine].
    /// Restrictions: None.
    /// Caution: 1. The preview function does not require you to log in to the room or publish the stream first. But after exiting the room, SDK internally actively stops previewing by default. 2. When this function is called, the audio engine module inside SDK will start, and it will start to try to collect audio.
    virtual void startPreview() = 0;

    /// Stops the local preview.
    ///
    /// Available since: 1.1.0
    /// Description: This function can be called to stop the preview when the preview is not needed locally.
    /// Caution: Stopping the preview will not affect the publish stream and playing stream functions.
    virtual void stopPreview() = 0;

    /// Stops the local preview (for the specified channel).
    ///
    /// Available since: 1.1.0
    /// Description: This function can be called to stop the preview when the preview is not needed locally.
    /// Caution: Stopping the preview will not affect the publish stream and playing stream functions.
    /// Note: This function is only available in ZegoExpressVideo SDK!
    ///
    /// @param channel Publish stream channel
    virtual void stopPreview(ZegoPublishChannel channel) = 0;

    /// Sets up the video configurations (for the specified channel).
    ///
    /// Available since: 1.1.0
    /// Description: Set the video frame rate, bit rate, video capture resolution, and video encoding output resolution.
    /// Default value: The default video capture resolution is 360p, the video encoding output resolution is 360p, the bit rate is 600 kbps, and the frame rate is 15 fps.
    /// When to call: After [createEngine].
    /// Restrictions: It is necessary to set the relevant video configuration before publishing the stream or startPreview, and only support the modification of the encoding resolution and the bit rate after publishing the stream.
    /// Caution: Developers should note that the wide and high resolution of the mobile end is opposite to the wide and high resolution of the PC. For example, in the case of 360p, the resolution of the mobile end is 360x640, and the resolution of the PC end is 640x360.
    /// Note: This function is only available in ZegoExpressVideo SDK!
    ///
    /// @param config Video configuration, the SDK provides a common setting combination of resolution, frame rate and bit rate, they also can be customized.
    /// @param channel Publish stream channel.
    virtual void setVideoConfig(ZegoVideoConfig config,
                                ZegoPublishChannel channel = ZEGO_PUBLISH_CHANNEL_MAIN) = 0;

    /// Gets the current video configurations (for the specified channel).
    ///
    /// This function can be used to get the specified publish channel's current video frame rate, bit rate, video capture resolution, and video encoding output resolution.
    /// Note: This function is only available in ZegoExpressVideo SDK!
    ///
    /// @param channel Publish stream channel
    /// @return Video configuration object
    virtual ZegoVideoConfig
    getVideoConfig(ZegoPublishChannel channel = ZEGO_PUBLISH_CHANNEL_MAIN) = 0;

    /// Sets the video mirroring mode (for the specified channel).
    ///
    /// Available since: 1.1.0
    /// Description: Set whether the local preview video and the published video have mirror mode enabled. For specific mirroring mode.
    /// When to call: After [createEngine].
    /// Restrictions: None.
    /// Note: This function is only available in ZegoExpressVideo SDK!
    ///
    /// @param mirrorMode Mirror mode for previewing or publishing the stream.
    /// @param channel Publish stream channel.
    virtual void setVideoMirrorMode(ZegoVideoMirrorMode mirrorMode,
                                    ZegoPublishChannel channel = ZEGO_PUBLISH_CHANNEL_MAIN) = 0;

#if TARGET_OS_IPHONE || defined(ANDROID)
    /// Sets the video orientation (for the specified channel).
    ///
    /// Available since: 1.1.0
    /// Description: Set the video orientation, please refer to https://doc-zh.zego.im/article/10365.
    /// Use cases: When users use mobile devices to conduct live broadcasts or video calls, they can set different video directions according to the scene.
    /// When to call: After [createEngine].
    /// Restrictions: None.
    /// Note: This function is only available in ZegoExpressVideo SDK!
    ///
    /// @param orientation Video orientation.
    /// @param channel Publish stream channel.
    virtual void setAppOrientation(ZegoOrientation orientation,
                                   ZegoPublishChannel channel = ZEGO_PUBLISH_CHANNEL_MAIN) = 0;
#endif

    /// Sets up the audio configurations for the specified publish channel.
    ///
    /// Available since: 1.3.4
    /// Description: You can set the combined value of the audio codec, bit rate, and audio channel through this function. If the preset value cannot meet the developer's scenario, the developer can set the parameters according to the business requirements.
    /// Default value: The default audio config refers to the default value of [ZegoAudioConfig].
    /// When to call: After the engine is created [createEngine], and before publishing [startPublishingStream].
    /// Restrictions: None.
    /// Related APIs: [getAudioConfig].
    ///
    /// @param config Audio config.
    /// @param channel Publish stream channel.
    virtual void setAudioConfig(ZegoAudioConfig config,
                                ZegoPublishChannel channel = ZEGO_PUBLISH_CHANNEL_MAIN) = 0;

    /// Gets the current audio configurations from the specified publish channel.
    ///
    /// Available since: 1.8.0
    /// Description: You can get the current audio codec, bit rate, and audio channel through this function.
    /// When to call: After the engine is created [createEngine].
    /// Restrictions: None.
    /// Related APIs: [setAudioConfig].
    ///
    /// @param channel Publish stream channel.
    /// @return Audio config.
    virtual ZegoAudioConfig
    getAudioConfig(ZegoPublishChannel channel = ZEGO_PUBLISH_CHANNEL_MAIN) = 0;

    /// Set encryption key for the publishing stream for the specified publish channel.
    ///
    /// Available since: 1.19.0
    /// Description: Support calling this function to update the encryption key while publishing stream.
    /// When to call: After the engine is created [createEngine], Called before and after [startPublishingStream] can both take effect.
    /// Restrictions: This function is only valid when publishing stream to the Zego RTC server.
    /// Caution: Note that developers need to update the player's decryption key before updating the publisher's encryption key.
    /// Related APIs: Calling [stopPublishingStream] or [logoutRoom] will clear the encryption key.
    ///
    /// @param key The encryption key, note that the key length only supports 16/24/32 bytes.
    /// @param channel Publish stream channel.
    virtual void
    setPublishStreamEncryptionKey(const std::string &key,
                                  ZegoPublishChannel channel = ZEGO_PUBLISH_CHANNEL_MAIN) = 0;

    /// Take a snapshot of the publishing stream for the specified publish channel.
    ///
    /// Available since: 1.17.0
    /// Description: Take a snapshot of the publishing stream.
    /// When to call: Called this function after calling [startPublishingStream] or [startPreview].
    /// Restrictions: None.
    /// Caution: The resolution of the snapshot is the encoding resolution set in [setVideoConfig]. If you need to change it to capture resolution, please call [setCapturePipelineScaleMode] to change the capture pipeline scale mode to [Post].
    /// Related callbacks: The screenshot result will be called back through [ZegoPublisherTakeSnapshotCallback].
    /// Related APIs: [takePlayStreamSnapshot].
    /// Note: This function is only available in ZegoExpressVideo SDK!
    ///
    /// @param callback Results of take publish stream snapshot.
    /// @param channel Publish stream channel.
    virtual void
    takePublishStreamSnapshot(ZegoPublisherTakeSnapshotCallback callback,
                              ZegoPublishChannel channel = ZEGO_PUBLISH_CHANNEL_MAIN) = 0;

    /// Stops or resumes sending the audio part of a stream for the specified channel.
    ///
    /// Available since: 1.1.0
    /// Description: This function can be called when publishing the stream to realize not publishing the audio data stream. The SDK still collects and processes the audio, but does not send the audio data to the network.
    /// When to call: Called after the engine is created [createEngine] can take effect.
    /// Restrictions: None.
    /// Related callbacks: If you stop sending audio streams, the remote user that play stream of local user publishing stream can receive `Mute` status change notification by monitoring [onRemoteMicStateUpdate] callbacks.
    /// Related APIs: [mutePublishStreamVideo].
    ///
    /// @param mute Whether to stop sending audio streams, true means not to send audio stream, and false means sending audio stream. The default is false.
    /// @param channel Publish stream channel.
    virtual void mutePublishStreamAudio(bool mute,
                                        ZegoPublishChannel channel = ZEGO_PUBLISH_CHANNEL_MAIN) = 0;

    /// Stops or resumes sending the video part of a stream for the specified channel.
    ///
    /// Available since: 1.1.0
    /// Description: This function can be called when publishing the stream to realize not publishing the video stream. The local camera can still work normally, can capture, preview and process video images normally, but does not send the video data to the network.
    /// When to call: Called after the engine is created [createEngine] can take effect.
    /// Restrictions: None.
    /// Related callbacks: If you stop sending video streams locally, the remote user that play stream of local user publishing stream can receive `Mute` status change notification by monitoring [onRemoteCameraStateUpdate] callbacks.
    /// Related APIs: [mutePublishStreamAudio].
    /// Note: This function is only available in ZegoExpressVideo SDK!
    ///
    /// @param mute Whether to stop sending video streams, true means not to send video stream, and false means sending video stream. The default is false.
    /// @param channel Publish stream channel.
    virtual void mutePublishStreamVideo(bool mute,
                                        ZegoPublishChannel channel = ZEGO_PUBLISH_CHANNEL_MAIN) = 0;

    /// Enable or disable the stream mixing precision alignment function.
    ///
    /// Available since: 2.11.0.
    /// Description: Use this interface to enable stream alignment, the SDK will attach network time information to the stream when publishing it for accurate stream alignment.
    /// Use case: Generally used in scenarios such as KTV where stream mixing alignment is required.
    /// When to call: After the engine is created [createEngine].
    /// Caution: If mixed flow need time for alignment, the flow through the network push flow need to call startPublishingStream and ZegoPublisherConfig.forceSynchronousNetworkTime = 1, for open network time synchronization.
    /// Related APIs: [startMixerTask], [startAutoMixerTask]
    ///
    /// @param alignment Whether to enable the stream mixing precision alignment function.
    /// @param channel Publish stream channel
    virtual void
    setStreamAlignmentProperty(int alignment,
                               ZegoPublishChannel channel = ZEGO_PUBLISH_CHANNEL_MAIN) = 0;

    /// Enables or disables the traffic control for the specified publish channel.
    ///
    /// Available since: 1.5.0
    /// Description: Enabling traffic control allows the SDK to adjust the audio and video streaming bitrate according to the current upstream network environment conditions, or according to the counterpart's downstream network environment conditions in a one-to-one interactive scenario, to ensure smooth results. At the same time, you can further specify the attributes of traffic control to adjust the corresponding control strategy.
    /// Default value: Enable.
    /// When to call: After the engine is created [createEngine], Called before [startPublishingStream] can take effect.
    /// Restrictions: Only support RTC publish.
    ///
    /// @param enable Whether to enable traffic control. The default is ture.
    /// @param property Adjustable property of traffic control, bitmask format. Should be one or the combinations of [ZegoTrafficControlProperty] enumeration. [AdaptiveFPS] as default.
    /// @param channel Publish stream channel.
    virtual void enableTrafficControl(bool enable, int property,
                                      ZegoPublishChannel channel = ZEGO_PUBLISH_CHANNEL_MAIN) = 0;

    /// Sets the minimum video bitrate for traffic control for the specified publish channel.
    ///
    /// Available since: 1.1.0
    /// Description: Set the control strategy when the video bitrate reaches the lowest threshold during flow control. When the bitrate is lower than the minimum threshold, you can choose not to send video data or send it at a very low frame bitrate.
    /// Default value: There is no control effect of the lowest threshold of video bitrate.
    /// When to call: After the engine is created [createEngine], Called before [startPublishingStream] can take effect.
    /// Restrictions: The traffic control must be turned on [enableTrafficControl].
    /// Related APIs: [enableTrafficControl].
    /// Note: This function is only available in ZegoExpressVideo SDK!
    ///
    /// @param bitrate Minimum video bitrate (kbps).
    /// @param mode Video sending mode below the minimum bitrate.
    /// @param channel Publish stream channel.
    virtual void
    setMinVideoBitrateForTrafficControl(int bitrate, ZegoTrafficControlMinVideoBitrateMode mode,
                                        ZegoPublishChannel channel = ZEGO_PUBLISH_CHANNEL_MAIN) = 0;

    /// Sets the minimum video frame rate threshold for traffic control.
    ///
    /// Available since: 2.17.0
    /// Description: Set the control policy when the video frame rate reaches the lowest threshold when flow control.
    /// Default value: There is no control effect of the lowest threshold of video frame rate.
    /// When to call: The call takes effect after the engine [createEngine] is created.
    /// Restrictions: The traffic control must be turned on [enableTrafficControl]. And its parameter [property] must contain AdaptiveFPS, Please refer to [ZegoTrafficControlProperty] for details.
    /// Related APIs: [enableTrafficControl].
    /// Caution: If you need to cancel the limit of the setting value, you can set it to 0.
    /// Note: This function is only available in ZegoExpressVideo SDK!
    ///
    /// @param fps The minimum video frame rate threshold for traffic control(fps).
    /// @param channel Publish stream channel.
    virtual void
    setMinVideoFpsForTrafficControl(int fps,
                                    ZegoPublishChannel channel = ZEGO_PUBLISH_CHANNEL_MAIN) = 0;

    /// Sets the minimum video resolution threshold for traffic control.
    ///
    /// Available since: 2.17.0
    /// Description: Set the control policy when the video resolution reaches the lowest threshold when flow control.
    /// Default value: There is no control effect of the lowest threshold of video resolution.
    /// When to call: The call takes effect after the engine [createEngine] is created.
    /// Restrictions: The traffic control must be turned on [enableTrafficControl]. And its parameter [property] must contain AdaptiveResolution, Please refer to [ZegoTrafficControlProperty] for details.
    /// Related APIs: [enableTrafficControl].
    /// Caution: If you need to cancel the limit of the setting value, you can set width and height to 0.
    /// Note: This function is only available in ZegoExpressVideo SDK!
    ///
    /// @param width The flow controls the width of the lowest video resolution.
    /// @param height The flow controls the height of the lowest video resolution.
    /// @param channel Publish stream channel.
    virtual void setMinVideoResolutionForTrafficControl(
        int width, int height, ZegoPublishChannel channel = ZEGO_PUBLISH_CHANNEL_MAIN) = 0;

    /// Set the factors of concern that trigger traffic control for the specified publish channel.
    ///
    /// Available since: 2.4.0
    /// Description: Use this interface to control whether to start traffic control due to poor remote network conditions.
    /// Default value: Default is disable.
    /// When to call: After the engine is created [createEngine], Called before [startPublishingStream] can take effect.
    /// Restrictions: The traffic control must be turned on [enableTrafficControl].
    /// Related APIs: [enableTrafficControl.
    ///
    /// @param mode When LOCAL_ONLY is selected, only the local network status is concerned. When choosing REMOTE, also take into account the remote network.
    /// @param channel Publish stream channel.
    virtual void
    setTrafficControlFocusOn(ZegoTrafficControlFocusOnMode mode,
                             ZegoPublishChannel channel = ZEGO_PUBLISH_CHANNEL_MAIN) = 0;

    /// Sets the audio recording volume for stream publishing.
    ///
    /// Available since: 1.13.0
    /// Description: This function is used to perform gain processing based on the device's collected volume. The local user can control the sound level of the audio stream sent to the remote end.
    /// Default value: Default is 100.
    /// When to call: After creating the engine [createEngine].
    /// Restrictions: The capture volume can be dynamically set during publishing.
    /// Related APIs: Set the playing stream volume [setPlayVolume].
    ///
    /// @param volume The volume gain percentage, the range is 0 ~ 200, and the default value is 100, which means 100% of the original collection volume of the device.
    virtual void setCaptureVolume(int volume) = 0;

    /// Set audio capture stereo mode.
    ///
    /// Available since: 1.15.0 (iOS/Android/Windows); support macOS since 2.16.0
    /// Description: This function is used to set the audio capture channel mode. When the developer turns on the stereo capture, using a special stereo capture device, the stereo audio data can be captured and streamed.
    /// Use cases: In some professional scenes, users are particularly sensitive to sound effects, such as voice radio and musical instrument performance. At this time, support for stereo and high-quality sound is required.
    /// Default value: The default is None, which means mono capture.
    /// When to call: It needs to be called after [createEngine]， before [startPublishingStream], [startPlayingStream], [startPreview], [createMediaPlayer], [createAudioEffectPlayer] and [createRealTimeSequentialDataManager].
    /// Restrictions: If you need to enable stereo capture, you also need to meet the following conditions: For iOS/Android, you need to connect an external audio device that supports stereo capture and be at the media volume. For macOS, it needs to be at the media volume. For Windows, an external audio device that supports stereo capture is required.
    /// Related APIs: When streaming, you need to enable the stereo audio encoding function through the [setAudioConfig] interface at the same time.
    ///
    /// @param mode Audio stereo capture mode.
    virtual void setAudioCaptureStereoMode(ZegoAudioCaptureStereoMode mode) = 0;

    /// Adds a target CDN URL to which the stream will be relayed from ZEGO RTC server.
    ///
    /// Available since: 1.1.0
    /// Description: Forward audio and video streams from ZEGO RTC servers to custom CDN content distribution networks with high latency but support for high concurrent pull streams.
    /// Use cases: 1. It is often used in large-scale live broadcast scenes that do not have particularly high requirements for delay. 2. Since ZEGO RTC server itself can be configured to support CDN(content distribution networks), this function is mainly used by developers who have CDN content distribution services themselves. 3. This function supports dynamic relay to the CDN content distribution network, so developers can use this function as a disaster recovery solution for CDN content distribution services.
    /// When to call: After calling the [createEngine] function to create the engine.
    /// Restrictions: When the [enablePublishDirectToCDN] function is set to true to publish the stream straight to the CDN, then calling this function will have no effect.
    /// Caution: Removing URLs retweeted to CDN requires calling [removePublishCdnUrl], calling [stopPublishingStream] will not remove URLs publish to CDN.
    /// Related APIs: Remove URLs that are re-pushed to the CDN [removePublishCdnUrl].
    ///
    /// @param streamID Stream ID.
    /// @param targetURL CDN relay address, supported address format is rtmp, rtmps.
    /// @param callback The execution result of update the relay CDN operation.
    virtual void addPublishCdnUrl(const std::string &streamID, const std::string &targetURL,
                                  ZegoPublisherUpdateCdnUrlCallback callback) = 0;

    /// Deletes the specified CDN URL, which is used for relaying streams from ZEGO RTC server to CDN.
    ///
    /// Available since: 1.1.0
    /// Description: When a CDN forwarding address has been added via [addPublishCdnUrl], this function is called when the stream needs to be stopped.
    /// When to call: After calling the [createEngine] function to create the engine, When you don't need to continue publish to the CDN.
    /// Restrictions: When the [enablePublishDirectToCDN] function is set to true to publish the stream straight to the CDN, then calling this function will have no effect.
    /// Caution: This function does not stop publishing audio and video stream to the ZEGO ZEGO RTC server.
    /// Related APIs: Add URLs that are re-pushed to the CDN [addPublishCdnUrl].
    ///
    /// @param streamID Stream ID.
    /// @param targetURL CDN relay address, supported address format rtmp.
    /// @param callback The execution result of update the relay CDN operation.
    virtual void removePublishCdnUrl(const std::string &streamID, const std::string &targetURL,
                                     ZegoPublisherUpdateCdnUrlCallback callback) = 0;

    /// Whether to directly push to CDN (without going through the ZEGO RTC server), for the specified channel.
    ///
    /// Available since: 1.5.0
    /// Description: Whether to publish streams directly from the client to CDN without passing through Zego RTC server.
    /// Use cases: It is often used in large-scale live broadcast scenes that do not have particularly high requirements for delay.
    /// Default value: The default is false, and direct push is not enabled.
    /// When to call: After creating the engine [createEngine], before starting to push the stream [startPublishingStream].
    /// Caution: The Direct Push CDN feature does not pass through the ZEGO Real-Time Audio and Video Cloud during network transmission, so you cannot use ZEGO's ultra-low latency audio and video services.
    /// Related APIs: Dynamic re-push to CDN function [addPublishCdnUrl], [removePublishCdnUrl].
    ///
    /// @param enable Whether to enable direct publish CDN, true: enable direct publish CDN, false: disable direct publish CDN.
    /// @param config CDN configuration, if nullptr, use Zego's background default configuration.
    /// @param channel Publish stream channel.
    virtual void
    enablePublishDirectToCDN(bool enable, ZegoCDNConfig *config,
                             ZegoPublishChannel channel = ZEGO_PUBLISH_CHANNEL_MAIN) = 0;

    /// Sets up the stream watermark before stream publishing (for the specified channel).
    ///
    /// Available since: 1.1.0
    /// Description: Set watermark for publish stream screen.
    /// Use cases: It is often used to identify the source of the publish.
    /// When to call: After creating the engine through [createEngine] function.
    /// Caution: The layout of the watermark cannot exceed the video encoding resolution of the stream. It can be set at any time before or during the publishing stream.
    /// Note: This function is only available in ZegoExpressVideo SDK!
    ///
    /// @param watermark The upper left corner of the watermark layout is the origin of the coordinate system, and the area cannot exceed the size set by the encoding resolution. If it is nullptr, the watermark is cancelled.
    /// @param isPreviewVisible the watermark is visible on local preview
    /// @param channel Publish stream channel.
    virtual void setPublishWatermark(ZegoWatermark *watermark, bool isPreviewVisible,
                                     ZegoPublishChannel channel = ZEGO_PUBLISH_CHANNEL_MAIN) = 0;

    /// Set the Supplemental Enhancement Information type.
    ///
    /// Available since: 1.18.0
    /// Description: By default, the SDK wraps the data with ZEGO's self-defined SEI type, which is not specified by the SEI standard. When the developer needs to use a third-party decoder to decode the SEI, the correct SEI will not be decoded and the [setSEIConfig] interface needs to be called to change the type of the SEI sent by the SDK to UserUnregister type.
    /// Use cases: This function needs to be executed when the developer uses a third-party decoder to decode the SEI.
    /// When to call: After creating the engine [createEngine], before starting to push the stream [startPublishingStream].
    /// Restrictions: None.
    ///
    /// @param config SEI configuration. The SEI defined by ZEGO is used by default.
    virtual void setSEIConfig(ZegoSEIConfig config) = 0;

    /// Sends Supplemental Enhancement Information.
    ///
    /// Available since: 1.1.0
    /// Description: While pushing the stream to transmit the audio and video stream data, the stream media enhancement supplementary information is sent to synchronize some other additional information.
    /// Use cases: Generally used in scenes such as synchronizing music lyrics or precise video layout, you can choose to send SEI.
    /// When to call: After starting to push the stream [startPublishingStream].
    /// Restrictions: Do not exceed 30 times per second, and the SEI data length is limited to 4096 bytes.
    /// Caution: Since the SEI information follows the video frame, there may be frame loss due to network problems, so the SEI information may also be lost. In order to solve this situation, it should be sent several times within the restricted frequency.
    /// Related APIs: After the pusher sends the SEI, the puller can obtain the SEI content by monitoring the callback of [onPlayerRecvSEI].
    ///
    /// @param data SEI data.
    /// @param dataLength SEI data length.
    /// @param channel Publish stream channel.
    virtual void sendSEI(const unsigned char *data, unsigned int dataLength,
                         ZegoPublishChannel channel = ZEGO_PUBLISH_CHANNEL_MAIN) = 0;

    /// Send the media supplementary enhancement information synchronized with the current video frame during custom video capture.
    ///
    /// Available since: 2.15.0
    /// Description: When using custom video capture, push the stream to transmit the video stream data, and send the stream media enhancement supplementary information to synchronize some other additional information, which is synchronized with the current video frame.
    /// Use cases: Generally used in scenes that need to be played back in strong synchronization with the video frame, such as video karaoke, video and lyrics are strongly synchronized; or scenes that need to be accurate to the frame level for strategic processing.
    /// When to call: To ensure that the SEI is synchronized with the current video frame, it must be called before sending the video frame data.
    /// Restrictions: Only used for custom video capture; only supports video-driven SEI sending; you should try to avoid calling this interface to send SEI continuously; to ensure that SEI is synchronized with the current video frame, it must be kept in the same thread as the interface for sending custom video frame data; SEI data length is limited to 4096 bytes.
    /// Caution: The sent SEI information follows the video frame. Due to network problems, there may be frame loss. At this time, the SEI will follow the next frame of video data. Therefore, in order to keep the SEI synchronized with the video frame, you should avoid sending SEI continuously; only when using SurfaceTexture on the Android platform , Need to pass the time stamp parameter timeStampNs, otherwise the parameter is invalid.
    /// Related APIs: After the pusher sends the SEI, the puller can obtain the SEI content by monitoring the callback of [onPlayerRecvSEI].
    ///
    /// @param data SEI data.
    /// @param dataLength SEI data length.
    /// @param timeStampNs video frame reference time, UNIX timestamp, in nanosecond.
    /// @param channel Publish stream channel.
    virtual void
    sendSEISyncWithCustomVideo(const unsigned char *data, unsigned int dataLength,
                               unsigned long long timeStampNs,
                               ZegoPublishChannel channel = ZEGO_PUBLISH_CHANNEL_MAIN) = 0;

    /// Send audio side information.
    ///
    /// Available since: 2.19.0
    /// Description: While streaming audio data, send audio side information to synchronize some additional information.
    /// Use cases: In the carousel scene, the audio data channel is required to carry accompanying information, such as timestamps to help align the accompaniment, and the need to know who the user is currently singing, whether to amplify the volume, and so on.
    /// When to call: After starting to push the stream [startPublishingStream].
    /// Restrictions: 1. This function is only valid when publishing stream to the Zego RTC server and it also doesn't work when retweeting the stream from the RTC server to the CDN. 2. The audio side information data length is limited to 1024 bytes.
    /// Caution: 1. Audio side information is driven by audio data, so audio data must be pushed (audio side information may be lost when the DTX function is enabled via the interface [setEngineConfig]). 2. Due to network issues, audio side information may be lost, and the SDK is responsible for transmission but does not guarantee reliability.
    /// Related APIs: After the pusher sends the side information, the puller can obtain the side information content by monitoring the callback of [onPlayerRecvAudioSideInfo].
    ///
    /// @param data Audio side info data.
    /// @param dataLength Audio side info data length.
    /// @param timeStampMs timeStampMs, derived from custom audio processing, in milliseconds. If you fill in 0, it is sent along with the frame that is currently ready to be sent.
    /// @param channel Publish stream channel.
    virtual void sendAudioSideInfo(const unsigned char *data, unsigned int dataLength,
                                   double timeStampMs,
                                   ZegoPublishChannel channel = ZEGO_PUBLISH_CHANNEL_MAIN) = 0;

    /// Enables or disables hardware encoding.
    ///
    /// Available since: 1.1.0
    /// Description: Whether to use the hardware encoding function when publishing the stream, the GPU is used to encode the stream and to reduce the CPU usage.
    /// When to call: The setting can take effect before the stream published. If it is set after the stream published, the stream should be stopped first before it takes effect.
    /// Caution: Because hard-coded support is not particularly good for a few models, SDK uses software encoding by default. If the developer finds that the device is hot when publishing a high-resolution audio and video stream during testing of some models, you can consider calling this function to enable hard coding.
    ///
    /// @param enable Whether to enable hardware encoding, true: enable hardware encoding, false: disable hardware encoding.
    virtual void enableHardwareEncoder(bool enable) = 0;

    /// Sets the timing of video scaling in the video capture workflow. You can choose to do video scaling right after video capture (the default value) or before encoding.
    ///
    /// Available since: 1.1.0
    /// When to call: This function needs to be set before call [startPreview] or [startPublishingStream].
    /// Caution: The main effect is Whether the local preview is affected when the acquisition resolution is different from the encoding resolution.
    /// Note: This function is only available in ZegoExpressVideo SDK!
    ///
    /// @param mode The capture scale timing mode.
    virtual void setCapturePipelineScaleMode(ZegoCapturePipelineScaleMode mode) = 0;

    /// Whether to enable H.265 encoding to automatically downgrade to H.264 encoding.
    ///
    /// Available since: 2.12.0
    /// Description: When using H.265 encoding to push the stream, whether to enable the strategy of automatically degrading H.265 encoding to H.264 encoding under abnormal circumstances.After enabling automatic downgrade, when H.265 encoding is not supported or H.265 encoding fails, the SDK will try to downgrade and use H.264 encoding to push the stream.After turning off automatic downgrade, when H.265 encoding is not supported or H.265 encoding fails, the direct streaming fails.
    /// Use cases: In the Co-hosting and Showroom Live Streaming scenarios, use H265 encoding to push the stream to save CDN traffic without degrading the picture quality.
    /// Default Value: When this interface is not called, the default is yes, which means that H.265 encoding is turned on and automatically downgraded to H.264 encoding.
    /// When to call: After creating the engine, call the [startPublishingStream] function before pushing the stream.
    /// Related callbacks: When the H.265 encoding is automatically downgraded to the H.264 encoding strategy, the [onPublisherVideoEncoderChanged] callback will be triggered when the encoding method changes.
    /// Caution: When downgrading from H.265 to H.264 encoding occurs during the streaming process, if you are recording local video or cloud recording, multiple recording files will be generated, which needs to be dealt with.
    ///
    /// @param enable Whether to enable H.265 coding automatically fallback to H.264 coding, true: enable, false: disable, and the default value is true
    virtual void enableH265EncodeFallback(bool enable) = 0;

    /// Whether the specified video encoding type is supported.
    ///
    /// Available since: 2.12.0 and above
    /// Description: Whether the specified video encoding is supported depends on the following aspects, whether the hardware model supports hard encoding, whether the performance of the hardware model supports soft encoding, and whether the SDK has the encoding module.
    /// When to call: After creating the engine.
    /// Caution: It is recommended that users call this interface to obtain H.265 encoding support capability before publish stream with H.265 encoding, if not supported, you can use other encodings for publish, such as H.264.On the mobile platform, the SDK only supports H.265 hardware encoding, and it is affected by the model and hardware capabilities. You need to call the [enableHardwareEncoder] function to enable hardware encoding, and then use this function to determine whether H.265 hardware encoding is supported.
    ///
    /// @param codecID Video codec id. Required: Yes.
    /// @return Whether the specified video encoding is supported.Value range: true means support, you can use this encoding format for publish; false means the is not supported, and the encoding format cannot be used for publish.
    virtual bool isVideoEncoderSupported(ZegoVideoCodecID codecID) = 0;

    /// Starts playing a stream from ZEGO RTC server.
    ///
    /// Available since: 1.1.0
    /// Description: Play audio and video streams from the ZEGO RTC server.
    /// Use cases: In the real-time scenario, developers can listen to the [onRoomStreamUpdate] event callback to obtain the new stream information in the room where they are located, and call this interface to pass in streamID for play streams.
    /// When to call: After [loginRoom].
    /// Restrictions: None.
    /// Caution: 1. The developer can update the player canvas by calling this function again (the streamID must be the same). 2. After the first play stream failure due to network reasons or the play stream is interrupted, the default time for SDK reconnection is 20min. 3. In the case of poor network quality, user play may be interrupted, the SDK will try to reconnect, and the current play status and error information can be obtained by listening to the [onPlayerStateUpdate] event. please refer to https://docs.zegocloud.com/faq/reconnect. 4. Playing the stream ID that does not exist, the SDK continues to try to play after calling this function. After the stream ID is successfully published, the audio and video stream can be actually played.
    /// Note: This function is only available in ZegoExpressVideo SDK!
    ///
    /// @param streamID Stream ID, a string of up to 256 characters. You cannot include URL keywords, otherwise publishing stream and playing stream will fails. Only support numbers, English characters and '~', '!', '@', '$', '%', '^', '&', '*', '(', ')', '_', '+', '=', '-', '`', ';', '’', ',', '.', '<', '>', '/', '\'.
    /// @param canvas The view used to display the play audio and video stream's image. When the view is set to [nullptr], no video is displayed, only audio is played.
    virtual void startPlayingStream(const std::string &streamID, ZegoCanvas *canvas) = 0;

    /// Starts playing a stream from ZEGO RTC server or from third-party CDN. Support multi-room mode.
    ///
    /// Available since: 1.1.0
    /// Description: Play audio and video streams from the ZEGO RTC server or CDN.
    /// Use cases: In real-time or live broadcast scenarios, developers can listen to the [onRoomStreamUpdate] event callback to obtain the new stream information in the room where they are located, and call this interface to pass in streamID for play streams.
    /// When to call: After [loginRoom].
    /// Restrictions: None.
    /// Caution: 1. The developer can update the player canvas by calling this function again (the streamID must be the same). 2. After the first play stream failure due to network reasons or the play stream is interrupted, the default time for SDK reconnection is 20min. 3. In the case of poor network quality, user play may be interrupted, the SDK will try to reconnect, and the current play status and error information can be obtained by listening to the [onPlayerStateUpdate] event. please refer to https://docs.zegocloud.com/faq/reconnect. 4. Playing the stream ID that does not exist, the SDK continues to try to play after calling this function. After the stream ID is successfully published, the audio and video stream can be actually played.
    /// Note: This function is only available in ZegoExpressVideo SDK!
    ///
    /// @param streamID Stream ID, a string of up to 256 characters. You cannot include URL keywords, otherwise publishing stream and playing stream will fails. Only support numbers, English characters and '~', '!', '@', '$', '%', '^', '&', '*', '(', ')', '_', '+', '=', '-', '`', ';', '’', ',', '.', '<', '>', '/', '\'.
    /// @param canvas The view used to display the play audio and video stream's image. When the view is set to [nullptr], no video is displayed, only audio is played.
    /// @param config Advanced player configuration.
    virtual void startPlayingStream(const std::string &streamID, ZegoCanvas *canvas,
                                    ZegoPlayerConfig config) = 0;

    /// Starts playing a stream from ZEGO RTC server.
    ///
    /// Available since: 1.1.0
    /// Description: Play audio streams from the ZEGO RTC server or CDN.
    /// Use cases: In the real-time scenario, developers can listen to the [onRoomStreamUpdate] event callback to obtain the new stream information in the room where they are located, and call this interface to pass in streamID for play streams.
    /// When to call: After [loginRoom].
    /// Restrictions: None.
    /// Caution: 1. After the first play stream failure due to network reasons or the play stream is interrupted, the default time for SDK reconnection is 20min. 2. In the case of poor network quality, user play may be interrupted, the SDK will try to reconnect, and the current play status and error information can be obtained by listening to the [onPlayerStateUpdate] event. please refer to https://docs.zegocloud.com/faq/reconnect. 3. Playing the stream ID that does not exist, the SDK continues to try to play after calling this function. After the stream ID is successfully published, the audio stream can be actually played.
    ///
    /// @param streamID Stream ID, a string of up to 256 characters. You cannot include URL keywords, otherwise publishing stream and playing stream will fails. Only support numbers, English characters and '~', '!', '@', '$', '%', '^', '&', '*', '(', ')', '_', '+', '=', '-', '`', ';', '’', ',', '.', '<', '>', '/', '\'.
    virtual void startPlayingStream(const std::string &streamID) = 0;

    /// Starts playing a stream from ZEGO RTC server or from third-party CDN.
    ///
    /// Available since: 1.1.0
    /// Description: Play audio streams from the ZEGO RTC server or CDN.
    /// Use cases: In real-time or live broadcast scenarios, developers can listen to the [onRoomStreamUpdate] event callback to obtain the new stream information in the room where they are located, and call this interface to pass in streamID for play streams.
    /// When to call: After [loginRoom].
    /// Restrictions: None.
    /// Caution: 1. After the first play stream failure due to network reasons or the play stream is interrupted, the default time for SDK reconnection is 20min. 2. In the case of poor network quality, user play may be interrupted, the SDK will try to reconnect, and the current play status and error information can be obtained by listening to the [onPlayerStateUpdate] event. please refer to https://docs.zegocloud.com/faq/reconnect. 3. Playing the stream ID that does not exist, the SDK continues to try to play after calling this function. After the stream ID is successfully published, the audio stream can be actually played.
    ///
    /// @param streamID Stream ID, a string of up to 256 characters. You cannot include URL keywords, otherwise publishing stream and playing stream will fails. Only support numbers, English characters and '~', '!', '@', '$', '%', '^', '&', '*', '(', ')', '_', '+', '=', '-', '`', ';', '’', ',', '.', '<', '>', '/', '\'.
    /// @param config Advanced player configuration.
    virtual void startPlayingStream(const std::string &streamID, ZegoPlayerConfig config) = 0;

    /// Stops playing a stream.
    ///
    /// Available since: 1.1.0
    /// Description: Play audio and video streams from the ZEGO RTC server.
    /// Use cases: In the real-time scenario, developers can listen to the [onRoomStreamUpdate] event callback to obtain the delete stream information in the room where they are located, and call this interface to pass in streamID for stop play streams.
    /// When to call: After [loginRoom].
    /// Restrictions: None.
    /// Caution: When stopped, the attributes set for this stream previously, such as [setPlayVolume], [mutePlayStreamAudio], [mutePlayStreamVideo], etc., will be invalid and need to be reset when playing the the stream next time.
    ///
    /// @param streamID Stream ID.
    virtual void stopPlayingStream(const std::string &streamID) = 0;

    /// Set decryption key for the playing stream.
    ///
    /// Available since: 1.19.0
    /// Description: When streaming, the audio and video data will be decrypted according to the set key.
    /// Use cases: Usually used in scenarios that require high security for audio and video calls.
    /// When to call: after [createEngine], after the play stream can be changed at any time.
    /// Restrictions: This function is only valid when calling from Zego RTC or L3 server.
    /// Related APIs: [setPublishStreamEncryptionKey]Set the publish stream encryption key.
    /// Caution: This interface can only be called if encryption is set on the publish. Calling [stopPlayingStream] or [logoutRoom] will clear the decryption key.
    ///
    /// @param streamID Stream ID.
    /// @param key The decryption key, note that the key length only supports 16/24/32 bytes.
    virtual void setPlayStreamDecryptionKey(const std::string &streamID,
                                            const std::string &key) = 0;

    /// Set up cross App playing stream information.
    ///
    /// Available since: 2.19.0
    /// Description: This information is used for authentication before playing a stream or when retrying playing a stream.
    /// Use cases: Used in scenarios that playing streams across apps.
    /// When to call: after [createEngine], after the play stream can be changed at any time.
    /// Restrictions: This function is only valid when playing stream from Zego RTC server.
    /// Caution: Calling [stopPlayingStream] or [logoutRoom] will clear this information.
    ///
    /// @param streamID Stream ID.
    /// @param info Information for cross App playing stream.
    virtual void setPlayStreamCrossAppInfo(const std::string &streamID, ZegoCrossAppInfo info) = 0;

    /// Take a snapshot of the playing stream.
    ///
    /// Available since: 1.17.0
    /// Description: Take a screenshot of the specified stream ID.
    /// When to call: after called [startPlayingStream].
    /// Restrictions: None.
    /// Related callbacks: [onPlayerTakeSnapshotResult] Screenshot data callback.
    /// Note: This function is only available in ZegoExpressVideo SDK!
    ///
    /// @param streamID Stream ID to be snapshot.
    /// @param callback Results of take play stream snapshot.
    virtual void takePlayStreamSnapshot(const std::string &streamID,
                                        ZegoPlayerTakeSnapshotCallback callback) = 0;

    /// Sets the stream playback volume.
    ///
    /// Available since: 1.16.0
    /// Description: Set the sound size of the stream, the local user can control the playback volume of the audio stream.
    /// When to call: after called [startPlayingStream].
    /// Restrictions: None.
    /// Related APIs: [setAllPlayStreamVolume] Set all stream volume.
    /// Caution: You need to reset after [stopPlayingStream] and [startPlayingStream]. This function and the [setAllPlayStreamVolume] function overwrite each other, and the last call takes effect.
    ///
    /// @param streamID Stream ID.
    /// @param volume Volume percentage. The value ranges from 0 to 200, and the default value is 100.
    virtual void setPlayVolume(const std::string &streamID, int volume) = 0;

    /// Sets the all stream playback volume.
    ///
    /// Available since: 2.3.0
    /// Description: Set the sound size of the stream, the local user can control the playback volume of the audio stream.
    /// When to call: after called [startPlayingStream].
    /// Restrictions: None.
    /// Related APIs: [setPlayVolume] Set the specified streaming volume.
    /// Caution: You need to reset after [stopPlayingStream] and [startPlayingStream]. Set the specified streaming volume and [setAllPlayStreamVolume] interface to override each other, and the last call takes effect.
    ///
    /// @param volume Volume percentage. The value ranges from 0 to 200, and the default value is 100.
    virtual void setAllPlayStreamVolume(int volume) = 0;

    /// Set play video stream type.
    ///
    /// Available since: 2.3.0
    /// Description: When the publish stream sets the codecID to SVC through [setVideoConfig], the puller can dynamically set and select different stream types (small resolution is one-half of the standard layer).
    /// Use cases: In general, when the network is weak or the rendered UI window is small, you can choose to pull videos with small resolutions to save bandwidth.
    /// When to call: before or after called [startPlayingStream].
    /// Restrictions: None.
    /// Note: This function is only available in ZegoExpressVideo SDK!
    ///
    /// @param streamID Stream ID.
    /// @param streamType Video stream type.
    virtual void setPlayStreamVideoType(const std::string &streamID,
                                        ZegoVideoStreamType streamType) = 0;

    /// Set the adaptive adjustment interval range of the buffer for playing stream.
    ///
    /// Available since: 2.1.0
    /// Description: Set the range of adaptive adjustment of the internal buffer of the sdk when streaming is 0-4000ms.
    /// Use cases: Generally, in the case of a poor network environment, adjusting and increasing the playback buffer of the pull stream will significantly reduce the audio and video freezes, but will increase the delay.
    /// When to call: after called [createEngine].
    /// Restrictions: None.
    /// Caution: When the upper limit of the cache interval set by the developer exceeds 4000ms, the value will be 4000ms. When the upper limit of the cache interval set by the developer is less than the lower limit of the cache interval, the upper limit will be automatically set as the lower limit.
    ///
    /// @param streamID Stream ID.
    /// @param minBufferInterval The lower limit of the buffer adaptation interval, in milliseconds. The default value is 0ms.
    /// @param maxBufferInterval The upper limit of the buffer adaptation interval, in milliseconds. The default value is 4000ms.
    virtual void setPlayStreamBufferIntervalRange(const std::string &streamID,
                                                  unsigned int minBufferInterval,
                                                  unsigned int maxBufferInterval) = 0;

    /// Set the weight of the pull stream priority.
    ///
    /// Available since: 1.1.0
    /// Description: Set the weight of the streaming priority.
    /// Use cases: This interface can be used when developers need to prioritize the quality of a stream in business. For example: in class scene, if students pull multiple streams, you can set high priority for teacher stream.
    /// When to call: after called [startPlayingStream].
    /// Restrictions: None.
    /// Caution: By default, all streams have the same weight. Only one stream can be set with high priority, whichever is set last. After the flow is stopped, the initial state is automatically restored, and all flows have the same weight.When the local network is not good, while ensuring the focus flow, other stalls may be caused more.
    ///
    /// @param streamID Stream ID.
    virtual void setPlayStreamFocusOn(const std::string &streamID) = 0;

    /// Whether the pull stream can receive the specified audio data.
    ///
    /// Available since: 1.1.0
    /// Description: In the process of real-time audio and video interaction, local users can use this function to control whether to receive audio data from designated remote users when pulling streams as needed. When the developer does not receive the audio receipt, the hardware and network overhead can be reduced.
    /// Use cases: Call this function when developers need to quickly close and restore remote audio. Compared to re-flow, it can greatly reduce the time and improve the interactive experience.
    /// When to call: This function can be called after calling [createEngine].
    /// Caution: This function is valid only when the [muteAllPlayStreamAudio] function is set to `false`.
    /// Related APIs: You can call the [muteAllPlayStreamAudio] function to control whether to receive all audio data. When the two functions [muteAllPlayStreamAudio] and [mutePlayStreamAudio] are set to `false` at the same time, the local user can receive the audio data of the remote user when the stream is pulled: 1. When the [muteAllPlayStreamAudio(true)] function is called, it is globally effective, that is, local users will be prohibited from receiving all remote users' audio data. At this time, the [mutePlayStreamAudio] function will not take effect whether it is called before or after [muteAllPlayStreamAudio].2. When the [muteAllPlayStreamAudio(false)] function is called, the local user can receive the audio data of all remote users. At this time, the [mutePlayStreamAudio] function can be used to control whether to receive a single audio data. Calling the [mutePlayStreamAudio(true, streamID)] function allows the local user to receive audio data other than the `streamID`; calling the [mutePlayStreamAudio(false, streamID)] function allows the local user to receive all audio data.
    ///
    /// @param streamID Stream ID.
    /// @param mute Whether it can receive the audio data of the specified remote user when streaming, "true" means prohibition, "false" means receiving, the default value is "false".
    virtual void mutePlayStreamAudio(const std::string &streamID, bool mute) = 0;

    /// Whether the pull stream can receive the specified video data.
    ///
    /// Available since: 1.1.0
    /// Description: In the process of real-time video and video interaction, local users can use this function to control whether to receive video data from designated remote users when pulling streams as needed. When the developer does not receive the audio receipt, the hardware and network overhead can be reduced.
    /// Use cases: This function can be called when developers need to quickly close and resume watching remote video. Compared to re-flow, it can greatly reduce the time and improve the interactive experience.
    /// When to call: This function can be called after calling [createEngine].
    /// Caution: This function is valid only when the [muteAllPlayStreamVideo] function is set to `false`. When you mute the video stream, the view remains at the last frame by default, if you need to clear the last frame, please contact ZEGO technical support.
    /// Related APIs: You can call the [muteAllPlayStreamVideo] function to control whether to receive all video data. When the two functions [muteAllPlayStreamVideo] and [mutePlayStreamVideo] are set to `false` at the same time, the local user can receive the video data of the remote user when the stream is pulled: 1. When the [muteAllPlayStreamVideo(true)] function is called, it will take effect globally, that is, local users will be prohibited from receiving all remote users' video data. At this time, the [mutePlayStreamVideo] function will not take effect whether it is called before or after [muteAllPlayStreamVideo]. 2. When the [muteAllPlayStreamVideo(false)] function is called, the local user can receive the video data of all remote users. At this time, the [mutePlayStreamVideo] function can be used to control whether to receive a single video data. Call the [mutePlayStreamVideo(true, streamID)] function, the local user can receive other video data other than the `streamID`; call the [mutePlayStreamVideo(false, streamID)] function, the local user can receive all the video data.
    /// Note: This function is only available in ZegoExpressVideo SDK!
    ///
    /// @param streamID Stream ID.
    /// @param mute Whether it is possible to receive the video data of the specified remote user when streaming, "true" means prohibition, "false" means receiving, the default value is "false".
    virtual void mutePlayStreamVideo(const std::string &streamID, bool mute) = 0;

    /// Can the pull stream receive all audio data.
    ///
    /// Available since: 2.4.0
    /// Description: In the process of real-time audio and video interaction, local users can use this function to control whether to receive audio data from all remote users when pulling streams (including the audio streams pushed by users who have newly joined the room after calling this function). By default, users can receive audio data pushed by all remote users after joining the room. When the developer does not receive the audio receipt, the hardware and network overhead can be reduced.
    /// Use cases: Call this function when developers need to quickly close and restore remote audio. Compared to re-flow, it can greatly reduce the time and improve the interactive experience.
    /// When to call: This function can be called after calling [createEngine].
    /// Related APIs: You can call the [mutePlayStreamAudio] function to control whether to receive a single piece of audio data. When the two functions [muteAllPlayStreamAudio] and [mutePlayStreamAudio] are set to `false` at the same time, the local user can receive the audio data of the remote user when the stream is pulled: 1. When the [muteAllPlayStreamAudio(true)] function is called, it takes effect globally, that is, local users will be prohibited from receiving audio data from all remote users. At this time, the [mutePlayStreamAudio] function will not take effect no matter if the [mutePlayStreamAudio] function is called before or after [muteAllPlayStreamAudio]. 2. When the [muteAllPlayStreamAudio(false)] function is called, the local user can receive the audio data of all remote users. At this time, the [mutePlayStreamAudio] function can be used to control whether to receive a single audio data. Calling the [mutePlayStreamAudio(true, streamID)] function allows the local user to receive audio data other than the `streamID`; calling the [mutePlayStreamAudio(false, streamID)] function allows the local user to receive all audio data.
    ///
    /// @param mute Whether it is possible to receive audio data from all remote users when streaming, "true" means prohibition, "false" means receiving, and the default value is "false".
    virtual void muteAllPlayStreamAudio(bool mute) = 0;

    /// Can the pull stream receive all video data.
    ///
    /// Available since: 2.4.0
    /// Description: In the process of real-time video and video interaction, local users can use this function to control whether to receive all remote users' video data when pulling the stream (including the video stream pushed by the new user who joins the room after calling this function). By default, users can receive video data pushed by all remote users after joining the room. When the developer does not receive the audio receipt, the hardware and network overhead can be reduced.
    /// Use cases: This function can be called when developers need to quickly close and resume watching remote video. Compared to re-flow, it can greatly reduce the time and improve the interactive experience.
    /// When to call: This function can be called after calling [createEngine].
    /// Caution: When you mute the video stream, the view remains at the last frame by default, if you need to clear the last frame, please contact ZEGO technical support.
    /// Related APIs: You can call the [mutePlayStreamVideo] function to control whether to receive a single piece of video data. When the two functions [muteAllPlayStreamVideo] and [mutePlayStreamVideo] are set to `false` at the same time, the local user can receive the video data of the remote user when the stream is pulled: 1. When the [muteAllPlayStreamVideo(true)] function is called, it will take effect globally, that is, the local user will be prohibited from receiving all remote users' video data. At this time, the [mutePlayStreamVideo] function will not take effect whether it is called before or after [muteAllPlayStreamVideo]. 2. When the [muteAllPlayStreamVideo(false)] function is called, the local user can receive the video data of all remote users. At this time, the [mutePlayStreamVideo] function can be used to control whether to receive a single video data. Call the [mutePlayStreamVideo(true, streamID)] function, the local user can receive other video data other than the `streamID`; call the [mutePlayStreamVideo(false, streamID)] function, the local user can receive all the video data.
    /// Note: This function is only available in ZegoExpressVideo SDK!
    ///
    /// @param mute Whether it is possible to receive all remote users' video data when streaming, "true" means prohibition, "false" means receiving, and the default value is "false".
    virtual void muteAllPlayStreamVideo(bool mute) = 0;

    /// Enables or disables hardware decoding.
    ///
    /// Available since: 1.1.0
    /// Description: Control whether hardware decoding is used when playing streams, with hardware decoding enabled the SDK will use the GPU for decoding, reducing CPU usage.
    /// Use cases: If developers find that the device heats up badly when playing large resolution audio and video streams during testing on some models, consider calling this function to enable hardware decoding.
    /// Default value: Hardware decoding is disabled by default when this interface is not called.
    /// When to call: This function needs to be called after [createEngine] creates an instance.
    /// Restrictions: None.
    /// Caution: Need to be called before calling [startPlayingStream], if called after playing the stream, it will only take effect after stopping the stream and re-playing it. Once this configuration has taken effect, it will remain in force until the next call takes effect.
    ///
    /// @param enable Whether to turn on hardware decoding switch, true: enable hardware decoding, false: disable hardware decoding.
    virtual void enableHardwareDecoder(bool enable) = 0;

    /// Enables or disables frame order detection.
    ///
    /// Available since: 1.1.0
    /// Description: Control whether to turn on frame order detection, on to not support B frames, off to support B frames.
    /// Use cases: Turning on frame order detection when pulling cdn's stream will prevent splash screens.
    /// Default value: Turn on frame order detection by default when this interface is not called.
    /// When to call: This function needs to be called after [createEngine] creates an instance.
    /// Restrictions: None.
    /// Caution: Turn off frame order detection during playing stream may result in a brief splash screen.
    /// Note: This function is only available in ZegoExpressVideo SDK!
    ///
    /// @param enable Whether to turn on frame order detection, true: enable check poc,not support B frames, false: disable check poc, support B frames.
    virtual void enableCheckPoc(bool enable) = 0;

    /// Whether the specified video decoding format is supported.
    ///
    /// Available since: 2.12.0
    /// Description: Whether the specified video decoding is supported depends on the following aspects: whether the hardware model supports hard decoding, whether the performance of the hardware model supports soft decoding, and whether the SDK includes the decoding module.
    /// When to call: After creating the engine.
    /// Caution: It is recommended that users call this interface to obtain the H.265 decoding support capability before pulling the H.265 stream. If it is not supported, the user can pull the stream of other encoding formats, such as H.264.
    ///
    /// @param codecID Video codec id.Required: Yes.
    /// @return Whether the specified video decoding format is supported; true means support, you can use this decoding format for playing stream; false means the is not supported, and the decoding format cannot be used for play stream.
    virtual bool isVideoDecoderSupported(ZegoVideoCodecID codecID) = 0;

    /// Set the play stream alignment properties.
    ///
    /// Available since: 2.14.0
    /// Description: When playing at the streaming end, control whether the playing RTC stream needs to be accurately aligned. If necessary, all the streams that contain precise alignment parameters will be aligned; if not, all streams are not aligned.
    /// Use case: It is often used in scenes that require mixed stream alignment such as KTV to ensure that users can switch between singing anchors, ordinary Maishangyu chat anchors, and Maixia audiences at any time during use.
    /// Default value: If this interface is not called, the default is not aligned.
    /// When to call: Called after [createEngine]. Call the interface repeatedly, and the latest setting is valid.
    /// Related APIs: Set the precise alignment parameter of the stream channel [setStreamAlignmentProperty].
    ///
    /// @param mode Setting the stream alignment mode.
    virtual void setPlayStreamsAlignmentProperty(ZegoStreamAlignmentMode mode) = 0;

    /// Starts a stream mixing task.
    ///
    /// Available since: 1.2.1
    /// Description: Initiate a mixing stream request to the ZEGO RTC server, the server will look for the stream currently being pushed, and mix the layers according to the parameters of the mixing stream task requested by the SDK. When you need to update a mixing task, that is, when the input stream increases or decreases, you need to update the input stream list. At this time, you can update the field of the [ZegoMixerTask] object inputList and call this function again to pass in the same [ZegoMixerTask] object to update the mixing task.
    /// Use cases: It is often used when multiple video images are required to synthesize a video using mixed streaming, such as education, live broadcast of teacher and student images.
    /// When to call: After calling [loginRoom] to log in to the room.
    /// Restrictions: None.
    /// Caution: Due to the performance considerations of the client device, the SDK muxing is to start the mixing task on the ZEGO RTC server for mixing. If an exception occurs when the mixing task is requested to start, for example, the most common mixing input stream does not exist, the error code will be given from the callback callback. If a certain input stream does not exist in the middle, the muxing task will automatically retry to pull this input stream for 90 seconds, and will not retry after 90 seconds. If all input streams no longer exist, the server will automatically stop the mixing task after 90 seconds.
    /// Related callbacks: [OnMixerRelayCDNStateUpdate] can be used to obtain the CDN status update notification of the mixed stream repost, and the sound update notification of each single stream in the mixed stream can be obtained through [onMixerSoundLevelUpdate].
    /// Related APIs: the mixing task can be stopped by the [stopMixerTask] function.
    ///
    /// @param task Mixing task object. Required: Yes.
    /// @param callback Start notification of mixing task results.Required: No. Caution: Passing [nullptr] means not receiving callback notifications.
    virtual void startMixerTask(ZegoMixerTask task, ZegoMixerStartCallback callback) = 0;

    /// Stops a stream mixing task.
    ///
    /// Available since: 1.2.1
    /// Description: Initiate a request to end the mixing task to the ZEGO RTC server.
    /// Use cases: It is often used when multiple video images are required to synthesize a video using mixed streaming, such as education, live broadcast of teacher and student images.
    /// When to call: After calling [startMixerTask] to start mixing.
    /// Restrictions: None.
    /// Caution: If the developer starts the next mixing task without stopping the previous mixing task, the previous mixing task will not automatically stop until the input stream of the previous mixing task does not exist for 90 seconds. Before starting the next mixing task, you should stop the previous mixing task, so that when an anchor has already started the next mixing task to mix with other anchors, the audience is still pulling the output stream of the previous mixing task.
    /// Related APIs: You can start mixing by using the [startMixerTask] function.
    ///
    /// @param task Mixing task object. Required: Yes.
    /// @param callback Stop stream mixing task result callback notification.Required: No. Caution: Passing [nullptr] means not receiving callback notifications.
    virtual void stopMixerTask(ZegoMixerTask task, ZegoMixerStopCallback callback) = 0;

    /// Starts an auto stream mixing task.
    ///
    /// Available since: 2.10.0
    /// Description: Local users can use this function to start an auto stream mixing task, all streams in a room wil be mixed. Currently, only audio streams can be mixed. When auto stream mixing is enabled, the audio of all streams in the room is automatically mixed, and any further pushed streams in the room are automatically mixed into the final output stream.
    /// Use cases: Often used in voice chat room scenarios.
    /// When to call: After the engine is created, user can call this function to enable auto stream mixing in the target room if the target room has already been created
    /// Restrictions: Please refer to https://docs.zegocloud.com/article/7611 or contact ZEGO technical support.
    /// Caution: Before starting the next auto stream mixing task in the same room, call [stopAutoMixerTask] function to end the last auto stream mixing task. Otherwise, when one anchor has started the next auto stream mixing task and other anchors have started the next auto stream mixing task, the audience still pulls the output stream of the first auto stream mixing task. If the user does not end the current auto stream mixing task, the task will automatically end after the room does not exist or the input streams do not exist for 90 seconds.
    /// Related callbacks: Users can obtain the execution result of the function through [ZegoMixerStartCallback] callback.Users can get automatic mixed flow information through [onAutoMixerSoundLevelUpdate] callback.
    /// Related APIs: Users can call [stopAutoMixerTask] function to stop an auto stream mixing task.
    ///
    /// @param task Auto mix stream task object
    /// @param callback Start auto mix stream task result callback notification
    virtual void startAutoMixerTask(ZegoAutoMixerTask task, ZegoMixerStartCallback callback) = 0;

    /// Stops an auto stream mixing task.
    ///
    /// Available since: 2.10.0
    /// Description: Local users can use this function to stop an auto stream mixing task.
    /// Use cases: Often used in voice chat room scenarios.
    /// When to call: Call this function after [startAutoMixerTask] function is called to start an auto stream mixing task.
    /// Caution: Before calling [startAutoMixerTask] function to start the next auto stream mixing task in the same room, call this function to end the last auto stream mixing task. Otherwise, when one anchor has started the next auto stream mixing task and other anchors have started the next auto stream mixing task, the audience still pulls the output stream of the first auto stream mixing task. If the user does not end the current auto stream mixing task, the task will automatically end after the room does not exist or the input streams do not exist for 90 seconds.
    /// Related callbacks: Users can obtain the execution result of the function through [ZegoMixerStopCallback] callback.
    /// Related APIs: Users can call [startAutoMixerTask] function to start an auto stream mixing task.
    ///
    /// @param task Auto mix stream task object
    /// @param callback Stop auto mix stream task result callback notification
    virtual void stopAutoMixerTask(ZegoAutoMixerTask task, ZegoMixerStopCallback callback) = 0;

    /// Mutes or unmutes the microphone.
    ///
    /// Available since: 1.1.0
    /// Description: This function is used to control whether to use the collected audio data. Mute (turn off the microphone) will use the muted data to replace the audio data collected by the device for streaming. At this time, the microphone device will still be occupied.
    /// Default value: The default is `false`, which means no muting.
    /// When to call: After creating the engine [createEngine].
    /// Restrictions: None.
    /// Related APIs: Developers who want to control whether to use microphone on the UI should use this function to avoid unnecessary performance overhead by using the [enableAudioCaptureDevice]. You can use [isMicrophoneMuted] to check if the microphone is muted.
    ///
    /// @param mute Whether to mute (disable) the microphone, `true`: mute (disable) microphone, `false`: enable microphone.
    virtual void muteMicrophone(bool mute) = 0;

    /// Checks whether the microphone is muted.
    ///
    /// Available since: 1.1.0
    /// Description: Used to determine whether the microphone is set to mute.
    /// When to call: After creating the engine [createEngine].
    /// Restrictions: None.
    /// Related APIs: [muteMicrophone].
    ///
    /// @return Whether the microphone is muted; true: the microphone is muted; `false`: the microphone is enable (not muted).
    virtual bool isMicrophoneMuted() = 0;

    /// Mutes or unmutes the audio output speaker.
    ///
    /// Available since: 1.1.0
    /// Description: After mute speaker, all the SDK sounds will not play, including playing stream, mediaplayer, etc. But the SDK will still occupy the output device.
    /// Default value: The default is `false`, which means no muting.
    /// When to call: After creating the engine [createEngine].
    /// Restrictions: None.
    ///
    /// @param mute Whether to mute (disable) speaker audio output, `true`: mute (disable) speaker audio output, `false`: enable speaker audio output.
    virtual void muteSpeaker(bool mute) = 0;

    /// Checks whether the audio output speaker is muted.
    ///
    /// Available since: 1.1.0
    /// Description: Used to determine whether the audio output is muted.
    /// When to call: After creating the engine [createEngine].
    /// Restrictions: None.
    /// Related APIs: [muteSpeaker].
    ///
    /// @return Whether the speaker is muted; `true`: the speaker is muted; `false`: the speaker is enable (not muted).
    virtual bool isSpeakerMuted() = 0;

    /// Gets a list of audio devices.
    ///
    /// Only supports Windows and Mac.
    ///
    /// @param deviceType Audio device type
    /// @return Audo device List
    virtual std::vector<ZegoDeviceInfo> getAudioDeviceList(ZegoAudioDeviceType deviceType) = 0;

    /// Get the device ID of the default audio device.
    ///
    /// Only supports Windows and Mac.
    ///
    /// @param deviceType Audio device type
    /// @return Default Audio device ID
    virtual std::string getDefaultAudioDeviceID(ZegoAudioDeviceType deviceType) = 0;

    /// Chooses to use the specified audio device.
    ///
    /// Available since: 1.0.0
    /// Description: Chooses to use the specified audio device.
    /// When to call: After creating the engine [createEngine] and before call [startPublishingStream] or [startPlayingStream].
    /// Restrictions: Only supports Windows/macOS.
    ///
    /// @param deviceType Audio device type
    /// @param deviceID ID of a device obtained by [getAudioDeviceList]
    virtual void useAudioDevice(ZegoAudioDeviceType deviceType, const std::string &deviceID) = 0;

    /// Get volume for the specified audio device.
    ///
    /// Get volume for the specified audio device. Only for Windows/macOS.
    ///
    /// @param deviceType Audio device type
    /// @param deviceID ID of a device obtained by [getAudioDeviceList]
    /// @return Device volume
    virtual int getAudioDeviceVolume(ZegoAudioDeviceType deviceType,
                                     const std::string &deviceID) = 0;

    /// Set volume for the specified audio device.
    ///
    /// Only for Windows/macOS. The direct operating system device may fail due to system restrictions. Please use [setCaptureVolume] and [setPlayVolume] first to adjust the volume of publish and play streams.
    ///
    /// @param deviceType Audio device type
    /// @param deviceID ID of a device obtained by [getAudioDeviceList]
    /// @param volume Device volume
    virtual void setAudioDeviceVolume(ZegoAudioDeviceType deviceType, const std::string &deviceID,
                                      int volume) = 0;

    /// Turn on audio device volume monitoring.
    ///
    /// Only for Windows/macOS.
    ///
    /// @param deviceType Audio device type
    /// @param deviceID ID of a device obtained by [getAudioDeviceList]
    virtual void startAudioDeviceVolumeMonitor(ZegoAudioDeviceType deviceType,
                                               const std::string &deviceID) = 0;

    /// Turn off audio device volume monitoring. Only for Windows/macOS.
    ///
    /// Only for Windows/macOS.
    ///
    /// @param deviceType Audio device type
    /// @param deviceID ID of a device obtained by [getAudioDeviceList]
    virtual void stopAudioDeviceVolumeMonitor(ZegoAudioDeviceType deviceType,
                                              const std::string &deviceID) = 0;

    /// Mutes or unmutes the audio device.
    ///
    /// Only for Windows/macOS.
    ///
    /// @param deviceType Audio device type
    /// @param deviceID ID of a device obtained by [getAudioDeviceList]
    /// @param mute Whether to mute the audio device; true means to mute the audio device; false means to unmute the audio device.
    virtual void muteAudioDevice(ZegoAudioDeviceType deviceType, const std::string &deviceID,
                                 bool mute) = 0;

    /// Check if the audio device is muted.
    ///
    /// Only for Windows/macOS.
    ///
    /// @param deviceType Audio device type
    /// @param deviceID ID of a device obtained by [getAudioDeviceList]
    /// @return Whether the audio device is muted; true means the audio device is muted; false means the audio device is not muted.
    virtual bool isAudioDeviceMuted(ZegoAudioDeviceType deviceType,
                                    const std::string &deviceID) = 0;

    /// Enables or disables the audio capture device.
    ///
    /// Available since: 1.1.0
    /// Description: This function is used to control whether to use the audio collection device. When the audio collection device is turned off, the SDK will no longer occupy the audio device. Of course, if the stream is being published at this time, there is no audio data.
    /// Use cases: When the user never needs to use the audio, you can call this function to close the audio collection.
    /// Default value: The default is `true`.
    /// When to call: After creating the engine [createEngine].
    /// Restrictions: None.
    /// Related APIs: Turning off or turning on the microphone on the hardware is a time-consuming operation, and there is a certain performance overhead when the user performs frequent operations. [muteMicrophone] is generally recommended.
    ///
    /// @param enable Whether to enable the audio capture device, `true`: enable audio capture device, `false`: disable audio capture device.
    virtual void enableAudioCaptureDevice(bool enable) = 0;

#if TARGET_OS_IPHONE || defined(ANDROID)
    /// get current audio route type.
    ///
    /// Available since: 1.1.0
    /// Description: Audio routing refers to the audio output device that an app uses to play audio, and common audio routes are: speakers, handsets, headphones, Bluetooth devices, and so on.
    /// When to call: After creating the engine [createEngine].
    /// Restrictions: None.
    /// Related APIs: Set audio route to speaker [setAudioRouteToSpeaker].
    virtual ZegoAudioRoute getAudioRouteType() = 0;
#endif

#if TARGET_OS_IPHONE || defined(ANDROID)
    /// Whether to use the built-in speaker to play audio.
    ///
    /// Available since: 1.1.0
    /// Description: Whether to use the speaker to play audio, when you choose not to use the built-in speaker to play the sound, the SDK will select the audio output device with the highest current priority to play the sound according to the system schedule, and common audio routes are: handsets, headphones, Bluetooth devices, and so on.
    /// When to call: After creating the engine [createEngine].
    /// Restrictions: None.
    /// Related APIs: Get the current audio route [getAudioRouteType].
    ///
    /// @param defaultToSpeaker Whether to use the built-in speaker to play sound, `true`: use the built-in speaker to play sound, `false`: use the highest priority audio output device scheduled by the current system to play sound
    virtual void setAudioRouteToSpeaker(bool defaultToSpeaker) = 0;
#endif

    /// Turns on/off the camera (for the specified channel).
    ///
    /// Available since: 1.1.0
    /// Description: This function is used to control whether to start the capture of the camera. After the camera is turned off, the video capture will not be performed. At this time, there will be no video data for local preview and push streaming.
    /// Default value: The default is `true` which means the camera is turned on.
    /// When to call: After creating the engine [createEngine].
    /// Restrictions: None.
    /// Caution: In the case of using the custom video capture function [enableCustomVideoCapture], since the developer has taken over the video data capture, the SDK is no longer responsible for the video data capture, but this function still affects whether to encode or not. Therefore, when developers use custom video capture, please ensure that the value of this function is `true`.
    /// Note: This function is only available in ZegoExpressVideo SDK!
    ///
    /// @param enable Whether to turn on the camera, `true`: turn on camera, `false`: turn off camera
    /// @param channel Publishing stream channel
    virtual void enableCamera(bool enable,
                              ZegoPublishChannel channel = ZEGO_PUBLISH_CHANNEL_MAIN) = 0;

#if TARGET_OS_IPHONE || defined(ANDROID)
    /// Switches to the front or the rear camera (for the specified channel).
    ///
    /// Available since: 1.1.0
    /// Description: This function is used to control the use of the front camera or the rear camera (only supported by Android and iOS).
    /// Default value: The default is `true` which means the front camera is used.
    /// When to call: After creating the engine [createEngine].
    /// Restrictions: None.
    /// Caution: When the custom video capture function [enableCustomVideoCapture] is turned on, since the developer has taken over the video data capture, the SDK is no longer responsible for the video data capture, and this function is no longer valid.
    /// Note: This function is only available in ZegoExpressVideo SDK!
    ///
    /// @param enable Whether to use the front camera, `true`: use the front camera, `false`: use the the rear camera.
    /// @param channel Publishing stream channel
    virtual void useFrontCamera(bool enable,
                                ZegoPublishChannel channel = ZEGO_PUBLISH_CHANNEL_MAIN) = 0;
#endif

#if TARGET_OS_IPHONE || defined(ANDROID)
    /// Whether the camera supports focusing.
    ///
    /// Available since: 2.14.0
    /// Description: Whether the camera supports focusing.
    /// Trigger: Called after turn on preview [startPreivew].
    /// Caution: Need to start the camera successfully.
    /// Note: This function is only available in ZegoExpressVideo SDK!
    ///
    /// @param channel Publishing stream channel
    /// @return Whether to support focus, support is true, not support is false.
    virtual bool isCameraFocusSupported(ZegoPublishChannel channel = ZEGO_PUBLISH_CHANNEL_MAIN) = 0;
#endif

#if TARGET_OS_IPHONE || defined(ANDROID)
    /// Set the camera focus mode.
    ///
    /// Available since: 2.14.0
    /// Description: Set the camera focus mode.
    /// Trigger: Called after turn on preview [startPreivew].
    /// Restrictions: Currently only supports iOS and Android platforms.
    /// Note: This function is only available in ZegoExpressVideo SDK!
    ///
    /// @param mode focus mode.
    /// @param channel Publishing stream channel
    virtual void setCameraFocusMode(ZegoCameraFocusMode mode,
                                    ZegoPublishChannel channel = ZEGO_PUBLISH_CHANNEL_MAIN) = 0;
#endif

#if TARGET_OS_IPHONE || defined(ANDROID)
    /// Set the focus point in the preview view.
    ///
    /// Available since: 2.14.0
    /// Description: Set the focus point in the preview view. (x, y) are the normalized coordinates in the preview view, that is, the ratio of the position of the focus point relative to the preview view and the width and height of the preview view. The upper left corner is (0, 0).
    /// Trigger: Called after turn on preview [startPreivew].
    /// Restrictions: Currently only supports iOS and Android platforms.
    /// Caution: Every time the camera restarts the acquisition, the settings will become invalid and need to be reset.
    /// Note: This function is only available in ZegoExpressVideo SDK!
    ///
    /// @param x Normalized X axis coordinate value, effective value [0,1].
    /// @param y Normalized Y axis coordinate value, effective value [0,1].
    /// @param channel Publishing stream channel
    virtual void
    setCameraFocusPointInPreview(float x, float y,
                                 ZegoPublishChannel channel = ZEGO_PUBLISH_CHANNEL_MAIN) = 0;
#endif

#if TARGET_OS_IPHONE || defined(ANDROID)
    /// Set the camera exposure mode.
    ///
    /// Available since: 2.14.0
    /// Description: Set the camera exposure mode.
    /// Trigger: Called after turn on preview [startPreivew].
    /// Restrictions: Currently only supports iOS and Android platforms.
    /// Note: This function is only available in ZegoExpressVideo SDK!
    ///
    /// @param mode Exposure mode.
    /// @param channel Publishing stream channel
    virtual void setCameraExposureMode(ZegoCameraExposureMode mode,
                                       ZegoPublishChannel channel = ZEGO_PUBLISH_CHANNEL_MAIN) = 0;
#endif

#if TARGET_OS_IPHONE || defined(ANDROID)
    /// Set the exposure point in the preview view.
    ///
    /// Available since: 2.14.0
    /// Description: Set the exposure point in the preview view. (x, y) are the normalized coordinates in the preview view, that is, the ratio of the position of the exposure point relative to the preview view and the width and height of the preview view. The upper left corner is (0, 0).
    /// Trigger: Called after turn on preview [startPreivew].
    /// Restrictions: Currently only supports iOS and Android platforms.
    /// Caution: Every time the camera restarts the acquisition, the settings will become invalid and need to be reset.
    /// Note: This function is only available in ZegoExpressVideo SDK!
    ///
    /// @param x Normalized X axis coordinate value, effective value [0,1].
    /// @param y Normalized Y axis coordinate value, effective value [0,1].
    /// @param channel Publishing stream channel
    virtual void
    setCameraExposurePointInPreview(float x, float y,
                                    ZegoPublishChannel channel = ZEGO_PUBLISH_CHANNEL_MAIN) = 0;
#endif

#if TARGET_OS_IPHONE || defined(ANDROID)
    /// Set the camera exposure compensation value.
    ///
    /// Available since: 2.10.0
    /// Description: Set the camera exposure compensation value.
    /// Use cases: User can call this function to set the camera exposure compensation value.
    /// When to call /Trigger: Called this function after calling [startPublishingStream] or [startPreview].
    /// Restrictions: None.
    /// Caution: The setting will be invalid when the camera is restarted.
    /// Platform differences: Only supports iOS and Android.
    /// Note: This function is only available in ZegoExpressVideo SDK!
    ///
    /// @param value Camera exposure, the value range is [-1,1], the default 0, -1 tends to darken, 1 tends to brighten.
    /// @param channel Publishing stream channel
    virtual void
    setCameraExposureCompensation(float value,
                                  ZegoPublishChannel channel = ZEGO_PUBLISH_CHANNEL_MAIN) = 0;
#endif

#if TARGET_OS_IPHONE || defined(ANDROID)
    /// Set the zoom factor of the camera. Every time the camera is restarted, the camera zoom factor will return to the initial value (1.0).
    ///
    /// Available since: 1.20.0
    /// Description: Set the camera zoom factor. Every time the camera is restarted, the camera zoom factor will be restored to its initial value.
    /// When to call: After creating the engine [createEngine].
    /// Restrictions: The settings will not take effect until the camera is started.
    /// Note: This function is only available in ZegoExpressVideo SDK!
    ///
    /// @param factor The zoom factor of the camera, the minimum value is 1.0, and the maximum value is the return value of [getCameraMaxZoomFactor].
    /// @param channel Publishing stream channel
    virtual void setCameraZoomFactor(float factor,
                                     ZegoPublishChannel channel = ZEGO_PUBLISH_CHANNEL_MAIN) = 0;
#endif

#if TARGET_OS_IPHONE || defined(ANDROID)
    /// Get the maximum zoom factor of the camera.
    ///
    /// Available since: 1.20.0
    /// Description: Set the camera zoom factor. Every time the camera is restarted, the camera zoom factor will be restored to its initial value.
    /// When to call: This is only available after the camera has been successfully started, and can generally be called when the captured first frame is received [onPublisherCapturedVideoFirstFrame] callback.
    /// Restrictions: None.
    /// Note: This function is only available in ZegoExpressVideo SDK!
    ///
    /// @param channel Publishing stream channel
    /// @return The maximum zoom factor of the camera.
    virtual float
    getCameraMaxZoomFactor(ZegoPublishChannel channel = ZEGO_PUBLISH_CHANNEL_MAIN) = 0;
#endif

    /// Enable camera adaptive frame rate.
    ///
    /// Available since: 2.20.0
    /// Description: After enabling, the SDK matches the capture frame rate range supported by the camera according to the set frame rate range, and dynamically adjusts the capture frame rate of the camera according to the ambient brightness within this range to improve the screen brightness when the set frame rate is too high.
    /// Use cases: The frame rate set by the user on the streaming end is too high, and the ambient lighting is low, so the subject cannot be displayed or recognized normally. For example, live broadcast scenes with high exposure requirements.
    /// When to call: After creating the engine [createEngine], before the camera starts.
    /// Caution: Takes When calling [setVideoConfig] to set the frame rate lower than the expected minimum frame rate, the frame rate value set by [setVideoConfig] will be used. Due to the different hardware and algorithm strategies of different mobile phone manufacturers, the effect of this interface is different on different models or on the front and rear cameras of the same model.
    /// Related APIs: Through [setVideoConfig], you can set the camera capture frame rate and the encoder encoding frame rate.
    ///
    /// @param enable Whether to enable camera adaptive frame rate. true means on, false means off.Off by default.
    /// @param minFPS Desired minimum frame rate, 15 recommended. Unit: fps.
    /// @param maxFPS Desired minimum frame rate, 25 recommended. Unit: fps.
    /// @param channel Publishing stream channel.
    virtual void
    enableCameraAdaptiveFPS(bool enable, int minFPS, int maxFPS,
                            ZegoPublishChannel channel = ZEGO_PUBLISH_CHANNEL_MAIN) = 0;

    /// Chooses to use the specified video device (for the specified channel).
    ///
    /// Only for Windows/macOS.
    /// Note: This function is only available in ZegoExpressVideo SDK!
    ///
    /// @param deviceID ID of a device obtained by getVideoDeviceList
    /// @param channel Publishing stream channel
    virtual void useVideoDevice(const std::string &deviceID,
                                ZegoPublishChannel channel = ZEGO_PUBLISH_CHANNEL_MAIN) = 0;

    /// Gets a list of video devices.
    ///
    /// Only for Windows/macOS.
    /// Note: This function is only available in ZegoExpressVideo SDK!
    ///
    /// @return Video device List
    virtual std::vector<ZegoDeviceInfo> getVideoDeviceList() = 0;

    /// Get the deviceID of the default video device.
    ///
    /// Only for Windows/macOS.
    /// Note: This function is only available in ZegoExpressVideo SDK!
    ///
    /// @return Default video device ID
    virtual std::string getDefaultVideoDeviceID() = 0;

    /// Starts sound level monitoring. Support setting the listening interval.
    ///
    /// Available since: 1.15.0
    /// Description: After starting monitoring, you can receive local audio sound level via [onCapturedSoundLevelUpdate] callback, and receive remote audio sound level via [onRemoteSoundLevelUpdate] callback. Before entering the room, you can call [startPreview] with this function and combine it with [onCapturedSoundLevelUpdate] callback to determine whether the audio device is working properly.
    /// Use cases: During the publishing and playing process, determine who is talking on the wheat and do a UI presentation.
    /// When to call: After the engine is created [createEngine].
    /// Caution:
    ///   1. [onCapturedSoundLevelUpdate] and [onRemoteSoundLevelUpdate] callback notification period is the value set by the parameter. If you want to use advanced feature of sound level, please use the function of the same name (the parameter type is ZegoSoundLevelConfig) instead.
    ///   2. After the sound monitoring is started, even if the local audio capture is not started, [onCapturedSoundLevelUpdate] will have a callback, and the sound level is 0.
    ///
    /// @param millisecond Monitoring time period of the sound level, in milliseconds, has a value range of [100, 3000]. Default is 100 ms.
    virtual void startSoundLevelMonitor(unsigned int millisecond = 100) = 0;

    /// Starts sound level monitoring. Support enable some advanced feature.
    ///
    /// Available since: 2.10.0
    /// Description: After starting monitoring, you can receive local audio sound level via [onCapturedSoundLevelUpdate] callback, and receive remote audio sound level via [onRemoteSoundLevelUpdate] callback. Before entering the room, you can call [startPreview] with this function and combine it with [onCapturedSoundLevelUpdate] callback to determine whether the audio device is working properly.
    /// Use cases: During the publishing and playing process, determine who is talking on the wheat and do a UI presentation.
    /// When to call: After the engine is created [createEngine].
    /// Caution:
    ///   1. [onCapturedSoundLevelUpdate] and [onRemoteSoundLevelUpdate] callback notification period is the value set by the parameter.
    ///   2. After the sound monitoring is started, even if the local audio capture is not started, [onCapturedSoundLevelUpdate] will have a callback, and the sound level is 0.
    ///
    /// @param config Configuration for starts the sound level monitor.
    virtual void startSoundLevelMonitor(ZegoSoundLevelConfig config) = 0;

    /// Stops sound level monitoring.
    ///
    /// Available since: 1.1.0
    /// Description: After the monitoring is stopped, the callback of the local/remote audio sound level will be stopped.
    /// When to call: After the engine is created [createEngine].
    /// Related APIs: Soundwave monitoring can be initiated via [startSoundLevelMonitor].
    virtual void stopSoundLevelMonitor() = 0;

    /// Starts audio spectrum monitoring. Support setting the listening interval.
    ///
    /// Available since: 1.15.0
    /// Description: After starting monitoring, you can receive local audio spectrum via [onCapturedAudioSpectrumUpdate] callback, and receive remote audio spectrum via [onRemoteAudioSpectrumUpdate] callback.
    /// Use cases: In the host K song scene, has been published or played under the premise that the host or audience to see the tone and volume change animation.
    /// When to call: After the engine is created [createEngine].
    /// Caution: [onCapturedAudioSpectrumUpdate] and [onRemoteAudioSpectrumUpdate] callback notification period is the value set by the parameter.
    ///
    /// @param millisecond Monitoring time period of the audio spectrum, in milliseconds, has a value range of [100, 3000]. Default is 100 ms.
    virtual void startAudioSpectrumMonitor(unsigned int millisecond = 100) = 0;

    /// Stops audio spectrum monitoring.
    ///
    /// Available since: 1.1.0
    /// Description: After the monitoring is stopped, the callback of the local/remote audio spectrum will be stopped.
    /// When to call: After the engine is created [createEngine].
    /// Related APIs: Audio spectrum monitoring can be initiated via [startAudioSpectrumMonitor].
    virtual void stopAudioSpectrumMonitor() = 0;

    /// Enables or disables headphone monitoring.
    ///
    /// Available since: 1.9.0
    /// Description: Enable/Disable headphone monitor, and users hear their own voices as they use the microphone to capture sounds.
    /// When to call: After the engine is created [createEngine].
    /// Default value: Disable.
    /// Caution:
    ///   1. This setting does not actually take effect until both the headset and microphone are connected.
    ///   2. The default is to return after acquisition and before pre-processing. If you need to return after pre-processing, please contact ZEGO technical support.
    ///
    /// @param enable Whether to use headphone monitor, true: enable, false: disable
    virtual void enableHeadphoneMonitor(bool enable) = 0;

    /// Sets the headphone monitor volume.
    ///
    /// Available since: 1.9.0
    /// Description: set headphone monitor volume.
    /// When to call: After the engine is created [createEngine].
    /// Caution: This setting does not actually take effect until both the headset and microphone are connected.
    /// Related APIs: Enables or disables headphone monitoring via [enableHeadphoneMonitor].
    ///
    /// @param volume headphone monitor volume, range from 0 to 200, 60 as default.
    virtual void setHeadphoneMonitorVolume(int volume) = 0;

    /// Enable or disable system audio capture.
    ///
    /// Available since: 1.9.0
    /// Description: Enable sound card capture to mix sounds played by the system into the publishing stream, such as sounds played by the browser, sounds played by the third-party player, etc.
    /// Default value: Default is disable.
    /// When to call: Called this function after calling [startPublishingStream] or [startPreview].
    /// Restrictions: None.
    /// Caution: The system sound card sound does not include streaming sound, media player sound and sound effect player sound.
    /// Related APIs: [setMixSystemPlayoutVolume] function can set system audio capture volume.
    /// Platform differences: Only supports Windows and macOS.
    ///
    /// @param enable Whether to mix system playout.
    virtual void enableMixSystemPlayout(bool enable) = 0;

    /// set system audio capture volume.
    ///
    /// Available since: 2.4.0
    /// Description:  set system audio capture volume.
    /// Use cases: User needs to adjust the volume which system playout mix to stream publishing.
    /// When to call /Trigger: Called this function after calling [startPublishingStream] or [startPreview].
    /// Restrictions: None.
    /// Related APIs: [enableMixSystemPlayout] enable or disable mix system playout.
    /// Platform differences: Only supports Windows and macOS.
    ///
    /// @param volume the volume. Valid range [0, 200], default is 100.
    virtual void setMixSystemPlayoutVolume(int volume) = 0;

    /// Enable or disable mix SDK playout to stream publishing.
    ///
    /// Available since: 1.0.0
    /// Description: Enable mix SDK playout sounds into the stream publishing.
    /// Use cases: Users need to mix the sound of SDK playout into stream publishing. For example, when the class scene, the teacher and student Co-hosting, and the teacher can mix the play streaming sound into the publish streaming.
    /// Default value: Default is disable.
    /// When to call /Trigger: Called this function after calling [startPublishingStream] or [startPreview].
    /// Restrictions: None.
    /// Platform differences: Only supports Windows and macOS.
    ///
    /// @param enable Whether to mix engine playout
    virtual void enableMixEnginePlayout(bool enable) = 0;

    /// Start audio VAD stable state monitoring.
    ///
    /// Available: since 2.14.0
    /// Description: After monitoring is started, you can use the [onAudioVADStateUpdate] callback to receive the specified type of audio VAD callback.
    /// Use cases: For example, when you specify the type of collection and use the microphone to collect, you can check whether the host has continuous and stable voice input through this interface.
    /// When to call: Before publish stream, you can call [startPreview] with this function and combine it with [onAudioVADStateUpdate] callback to determine whether the audio device is working properly.
    /// Restrictions: [onAudioVADStateUpdate] callback notification period is 3 seconds.
    /// Related APIs: [stopAudioVADStableStateMonitor].
    ///
    /// @param type audio VAD monitor type.
    virtual void startAudioVADStableStateMonitor(ZegoAudioVADStableStateMonitorType type) = 0;

    /// Start audio VAD stable state monitoring, and the monitoring period can be set.
    ///
    /// Available: since 2.17.0
    /// Description: After monitoring is started, you can use the [onAudioVADStateUpdate] callback to receive the specified type of audio VAD callback.
    /// Use cases: For example, when you specify the type of collection and use the microphone to collect, you can check whether the host has continuous and stable voice input through this interface.
    /// When to call: Before publish stream, you can call [startPreview] with this function and combine it with [onAudioVADStateUpdate] callback to determine whether the audio device is working properly.
    /// Restrictions: None.
    /// Related APIs: [stopAudioVADStableStateMonitor].
    ///
    /// @param type audio VAD monitor type.
    /// @param millisecond monitoring period
    virtual void startAudioVADStableStateMonitor(ZegoAudioVADStableStateMonitorType type,
                                                 int millisecond) = 0;

    /// Stop audio VAD stable state monitoring.
    ///
    /// Available: since 2.14.0
    /// Description: After calling this interface, the specified type of [onAudioVADStateUpdate] callback can no longer be received.
    /// When to call: None.
    /// Restrictions: None.
    /// Related APIs: [startAudioVADStableStateMonitor].
    ///
    /// @param type audio VAD monitor type.
    virtual void stopAudioVADStableStateMonitor(ZegoAudioVADStableStateMonitorType type) = 0;

    /// Get the audio device information currently in use.
    ///
    /// Available since: 2.12.0
    /// Description: Get the audio device information currently in use.
    /// Use cases: Used for scenes that need to manually switch between multiple audio devices.
    /// When to call: Called this function after calling [startPublishingStream] or [startPreview].
    /// Restrictions: Only supports Windows and macOS.
    /// Related APIs: The default audio device ID can be obtained through [getDefaultAudioDeviceID].
    ///
    /// @param deviceType Audio device type.Required:Yes.
    /// @return Audio device information.
    virtual ZegoDeviceInfo getCurrentAudioDevice(ZegoAudioDeviceType deviceType) = 0;

    /// Whether to enable acoustic echo cancellation (AEC).
    ///
    /// Available since: 1.1.0
    /// Description: Turning on echo cancellation, the SDK filters the collected audio data to reduce the echo component in the audio.
    /// Use case: When you need to reduce the echo to improve the call quality and user experience, you can turn on this feature.
    /// Default value: When this function is not called, iOS turns off echo cancellation by default and other platforms turn on echo cancellation by default
    /// When to call: It needs to be called after [createEngine], before [startPublishingStream], [startPlayingStream], [startPreview], [createMediaPlayer], [createAudioEffectPlayer] and [createRealTimeSequentialDataManager].
    /// Caution: The AEC function only supports the processing of sounds playbacked through the SDK, such as sounds played by the playing stream, media player, audio effect player, etc.
    /// Restrictions: None.
    /// Related APIs: Developers can use [enableHeadphoneAEC] to set whether to enable AEC when using headphones, and use [setAECMode] to set the echo cancellation mode.
    ///
    /// @param enable Whether to enable echo cancellation, true: enable, false: disable
    virtual void enableAEC(bool enable) = 0;

#if TARGET_OS_IPHONE || defined(ANDROID)
    /// Whether to turn on acoustic echo cancellation (AEC) when using the headphone.
    ///
    /// Available since: 1.1.0
    /// Description: When [enableAEC] is used to turn on echo cancellation, it is only turned on when the speaker is used for mobile terminal equipment. Call this function if you need to turn echo cancellation on or off when using the headset.
    /// Use case: It is common when the mobile device is connected to a external sound card as the audio output source. In order to eliminate the echo in this case, you need to call this function to turn on the echo cancellation.
    /// Default value: Android is off by default and iOS is on by default.
    /// When to call: It needs to be called after [createEngine], before [startPublishingStream], [startPlayingStream], [startPreview], [createMediaPlayer], [createAudioEffectPlayer] and [createRealTimeSequentialDataManager].
    /// Caution: Turning on echo cancellation will increase the ear return delay. On the iOS platform, the SDK cannot distinguish between the headset and the external sound card. If you use this function to turn off the system echo cancellation when using the headset, the sound played by the external sound card will be collected when the user accesses the external sound card.
    /// Restrictions: None.
    /// Related APIs: When the headset is not used, you can set whether the SDK turns on echo cancellation through [enableAEC].
    /// Platform differences: Only supports iOS and Android.
    ///
    /// @param enable Whether to enable, true: enable, false: disable
    virtual void enableHeadphoneAEC(bool enable) = 0;
#endif

    /// Sets the acoustic echo cancellation (AEC) mode.
    ///
    /// Available since: 1.1.0
    /// Description: When [enableAEC] is used to enable echo cancellation, this function can be used to switch between different echo cancellation modes to control the degree of echo cancellation.
    /// Use case: When the default echo cancellation effect does not meet expectations, this function can be used to adjust the echo cancellation mode.
    /// Default value: When this function is not called, the default echo cancellation mode is [Aggressive].
    /// When to call: It needs to be called after [createEngine], before [startPublishingStream], [startPlayingStream], [startPreview], [createMediaPlayer], [createAudioEffectPlayer] and [createRealTimeSequentialDataManager].
    /// Restrictions: The value set by this function is valid only after the echo cancellation function is turned on.
    ///
    /// @param mode Echo cancellation mode
    virtual void setAECMode(ZegoAECMode mode) = 0;

    /// Enables or disables automatic gain control (AGC).
    ///
    /// Available since: 1.1.0
    /// Description: After turning on this function, the SDK can automatically adjust the microphone volume to adapt to near and far sound pickups and keep the volume stable.
    /// Use case: When you need to ensure volume stability to improve call quality and user experience, you can turn on this feature.
    /// Default value: When this function is not called, AGC is enabled by default.
    /// When to call: It needs to be called after [createEngine] and before [startPublishingStream], [startPlayingStream], [startPreview], [createMediaPlayer], [createAudioEffectPlayer] and [createRealTimeSequentialDataManager]. Note that the Mac needs to be called after [startPreview] and before [startPublishingStream].
    /// Restrictions: None.
    ///
    /// @param enable Whether to enable automatic gain control, true: enable, false: disable
    virtual void enableAGC(bool enable) = 0;

    /// Enables or disables active noise suppression (ANS, aka ANC).
    ///
    /// Available since: 1.1.0
    /// Description: Enable the noise suppression can reduce the noise in the audio data and make the human voice clearer.
    /// Use case: When you need to suppress noise to improve call quality and user experience, you can turn on this feature.
    /// Default value: When this function is not called, ANS is enabled by default.
    /// When to call: It needs to be called after [createEngine], before [startPublishingStream], [startPlayingStream], [startPreview], [createMediaPlayer], [createAudioEffectPlayer] and [createRealTimeSequentialDataManager].
    /// Related APIs: This function has a better suppression effect on continuous noise (such as the sound of rain, white noise). If you need to turn on transient noise suppression, please use [enableTransientANS]. And the noise suppression mode can be set by [setANSMode].
    /// Restrictions: None.
    ///
    /// @param enable Whether to enable noise suppression, true: enable, false: disable
    virtual void enableANS(bool enable) = 0;

    /// Enables or disables transient noise suppression.
    ///
    /// Available since: 1.17.0
    /// Description: Enable the transient noise suppression can suppress the noises such as keyboard and desk knocks.
    /// Use case: When you need to suppress transient noise to improve call quality and user experience, you can turn on this feature.
    /// Default value: When this function is not called, this is disabled by default.
    /// When to call: It needs to be called after [createEngine], before [startPublishingStream], [startPlayingStream], [startPreview], [createMediaPlayer], [createAudioEffectPlayer] and [createRealTimeSequentialDataManager].
    /// Related APIs: This function will not suppress normal noise after it is turned on. If you need to turn on normal noise suppression, please use [enableANS].
    /// Restrictions: None.
    ///
    /// @param enable Whether to enable transient noise suppression, true: enable, false: disable
    virtual void enableTransientANS(bool enable) = 0;

    /// Sets the automatic noise suppression (ANS) mode.
    ///
    /// Available since: 1.1.0
    /// Description: When [enableANS] is used to enable noise suppression, this function can be used to switch between different noise suppression modes to control the degree of noise suppression.
    /// Use case: When the default noise suppression effect does not meet expectations, this function can be used to adjust the noise suppression mode.
    /// Default value: When this function is not called, the default echo cancellation mode is [Medium].
    /// When to call: It needs to be called after [createEngine], before [startPublishingStream], [startPlayingStream], [startPreview], [createMediaPlayer], [createAudioEffectPlayer] and [createRealTimeSequentialDataManager].
    /// Restrictions: The value set by this function is valid only after the noise suppression function is turned on.
    ///
    /// @param mode Audio Noise Suppression mode
    virtual void setANSMode(ZegoANSMode mode) = 0;

    /// Enables or disables audio mixing function.
    ///
    /// Available since: 1.9.0, will be deprecated soon. It is recommended to use the media player [createMediaPlayer] or the audio effect player [createAudioEffectPlayer] to implement the audio mixing function.
    /// Description: After the audio mixing function is turned on, the SDK will mix the audio data prepared by the developer with the audio data collected by the SDK before publishing.
    /// Use case: Developers can use this function when they need to mix their own songs, sound effects or other audio data into the publishing stream.
    /// Default value: When this function is not called, this is disabled by default.
    /// When to call: It needs to be called after [createEngine].
    /// Related APIs: After enabling audio mixing, the developer also needs to call [setAudioMixingHandler] to set the audio mixing callback, so as to provide the SDK with the audio data that needs to be mixed in the [onAudioMixingCopyData] callback.
    /// Caution: After you start audio mixing, the SDK will play the mixed audio on the local (publisher side) by default. If you do not want to play it locally but only on the remote (player side), please call [muteLocalAudioMixing] to set the local audio mixing mute. Recommend to use audio effect player or media player for audio mixing.
    /// Restrictions: None.
    ///
    /// @param enable Whether to enable audio mixting, true: enable, false: disable
    virtual void enableAudioMixing(bool enable) = 0;

    /// Sets up the audio mixing event handler.
    ///
    /// Available since: 1.9.0
    /// Description: After the audio mixing function is turned on, the SDK will mix the audio data prepared by the developer with the audio data collected by the SDK before publishing.
    /// Use case: Developers can use this function when they need to mix their own songs, sound effects or other audio data into the publishing stream.
    /// When to call: It needs to be called after [createEngine].
    /// Caution: When this function is called again to set the callback, the previously set mixing callback will be overwritten.
    /// Restrictions: None.
    ///
    /// @param handler Audio mixing callback handler
    virtual void setAudioMixingHandler(std::shared_ptr<IZegoAudioMixingHandler> handler) = 0;

    /// Mute or resume local playback of the mixing audio.
    ///
    /// Available since: 1.9.0
    /// Description: When calling this function to mute the local playback audio mixing, the local (publisher side) will not play the audio provided to the SDK through [onAudioMixingCopyData], but the remote (player side) can still playback it Mix.
    /// Use case: When developers need to mix their own songs, sound effects or other audio data into the publishing stream, but the mixed audio only wants to be heard by the remote player, and does not want to be playback locally, you can use this function.
    /// Default value: When this function is not called, the default is not mute, which is false.
    /// When to call: It needs to be called after [createEngine].
    /// Restrictions: None.
    ///
    /// @param mute Whether to mute local audio mixting, true: mute, false: unmute
    virtual void muteLocalAudioMixing(bool mute) = 0;

    /// Sets the audio mixing output volume for either local playback or the stream to published.
    ///
    /// Available since: 1.9.0
    /// Description: After enabling the audio mixing function through [enableAudioMixing], the developer can use this function to set the volume of the mixing audio to be mixed to SDK.
    /// Use case: When developers need to mix their own songs, sound effects or other audio data into the publishing stream, and want to adjust the volume of the mixing audio, you can use this function.
    /// When to call: It needs to be called after [createEngine].
    /// Caution: This function can individually set the mixing audio volume of the local playback or the remote playback.
    /// Restrictions: None.
    ///
    /// @param volume The audio mixing volume, range from 0 to 200, 100 as default.
    /// @param type Local playback volume / Remote playback volume
    virtual void setAudioMixingVolume(int volume, ZegoVolumeType type) = 0;

    /// Enable the Effects beauty environment.
    ///
    /// Available since: 2.16.0
    /// Description: Enable the Effects beauty environment. The SDK uses the specified video frame data type for transmission. The Windows platform only supports video frame raw data, the Apple platform only supports CVPixelBuffer, and the Android platform only supports texture2d.
    /// Use cases: It is often used in scenes such as video calls and live broadcasts.
    /// Default value: When this function is not called, the beauty environment is not activated by default.
    /// When to call: Must be called before calling [startPreview], [startPublishingStream]. If you need to modify the configuration, please call [logoutRoom] to log out of the room first, otherwise it will not take effect.
    /// Related APIs: [enableEffectsBeauty] switch beauty, [setEffectsBeautyParam] set beauty parameters.
    /// Caution: This beauty function is the basic function. If it does not meet the expectations of the developer, you can use the custom video pre-processing function [enableCustomVideoProcessing] or the custom video capture function [enableCustomVideoCapture] docking and constructing the AI ​​vision SDK [ZegoEffects] https://doc-zh.zego.im/article/9556 for best results.
    /// Restrictions: This function only supports Android system 5.0 and above, Android SDK version 21 and above.
    /// Note: This function is only available in ZegoExpressVideo SDK!
    virtual void startEffectsEnv() = 0;

    /// Disable the Effects beauty environment.
    ///
    /// Available since: 2.16.0
    /// Description: Disable the Effects beauty environment.
    /// Use cases: It is often used in scenes such as video calls and live broadcasts.
    /// When to call: Must be called before calling [startPreview], [startPublishingStream]. If you need to modify the configuration, please call [logoutRoom] to log out of the room first, otherwise it will not take effect.
    /// Related APIs: [enableEffectsBeauty] switch beauty, [setEffectsBeautyParam] set beauty parameters.
    /// Caution: This beauty function is the basic function. If it does not meet the expectations of the developer, you can use the custom video pre-processing function [enableCustomVideoProcessing] or the custom video capture function [enableCustomVideoCapture] docking and constructing the AI ​​vision SDK [ZegoEffects] for best results.
    /// Restrictions: This function only supports Android system 5.0 and above, Android SDK version 21 and above.
    /// Note: This function is only available in ZegoExpressVideo SDK!
    virtual void stopEffectsEnv() = 0;

    /// Enables or disables the beauty effect.
    ///
    /// Available since: 2.16.0
    /// Description: Support basic beauty functions, including whiten, rosy, smooth, and sharpen.
    /// Use cases: It is often used in scenes such as video calls and live broadcasts.
    /// When to call: You must call [startEffectsEnv] to enable the beauty environment before calling this function.
    /// Default value: When this function is not called, the beauty effect is not enabled by default.
    /// Related APIs: You can call the [setBeautifyOption] function to adjust the beauty parameters.
    /// Caution: This beauty function is the basic function. If it does not meet the expectations of the developer, you can use the custom video pre-processing function [enableCustomVideoProcessing] or the custom video capture function [enableCustomVideoCapture] docking and constructing the AI ​​vision SDK [ZegoEffects] for best results.
    /// Restrictions: If this function is used on the Android platform, it only supports 5.0 and above, SDK version 21 and above.
    /// Note: This function is only available in ZegoExpressVideo SDK!
    ///
    /// @param enable Whether to enable the beauty effect, true is enabled; false is disabled, and the default is false.
    virtual void enableEffectsBeauty(bool enable) = 0;

    /// Set beautify param.
    ///
    /// Available since: 2.16.0
    /// Description: Set the beauty parameters, including whiten, rosy, smooth, and sharpen.
    /// Use cases: It is often used in scenes such as video calls and live broadcasts.
    /// When to call: You must call [startEffectsEnv] to enable the beauty environment before calling this function.
    /// Related APIs: You can call [enableEffectsBeauty] to turn on or off the beauty function.
    /// Restrictions: This function only supports Android system 5.0 and above, Android SDK version 21 and above.
    /// Note: This function is only available in ZegoExpressVideo SDK!
    ///
    /// @param param Beauty option param.
    virtual void setEffectsBeautyParam(ZegoEffectsBeautyParam param) = 0;

    /// Set the sound equalizer (EQ).
    ///
    /// Available since: 1.12.0
    /// Description: Call this function to set the sound equalizer adjust the tone.
    /// Use cases: Often used in voice chatroom, KTV.
    /// When to call: It needs to be called after [createEngine].
    /// Restrictions: None.
    ///
    /// @param bandIndex Band frequency index, the value range is [0, 9], corresponding to 10 frequency bands, and the center frequencies are [31, 62, 125, 250, 500, 1K, 2K, 4K, 8K, 16K] Hz.
    /// @param bandGain Band gain for the index, the value range is [-15, 15]. Default value is 0, if all gain values in all frequency bands are 0, EQ function will be disabled.
    virtual void setAudioEqualizerGain(int bandIndex, float bandGain) = 0;

    /// Setting up the voice changer via preset enumeration.
    ///
    /// Available since: 1.17.0
    /// Description: Call this function to use preset voice changer effect.
    /// Use cases: Often used in live broadcasting, voice chatroom and KTV.
    /// When to call: It needs to be called after [createEngine].
    /// Restrictions: Voice changer effect is only effective for SDK captured sound.
    /// Related APIs:
    /// If you need advanced voice changer effect, please use [setVoiceChangerParam].
    /// This function is mutually exclusive with [setReverbPreset]. If used at the same time, it will produce undefined effect.
    /// Using ANDROID/ETHEREAL preset voice changer effect will modify reverberation or reverberation echo parameters. Calling [setVoiceChangerParam], [setReverbAdvancedParam], [setReverbEchoParam] may affect the voice changer effect after use these preset voice changer effect.
    /// If you need advanced reverb/echo/electronic effects/voice changer effect, please use [setReverbAdvancedParam], [setReverbEchoParam], [setElectronicEffects], [setVoiceChangerParam] together.
    ///
    /// @param preset The voice changer preset enumeration.
    virtual void setVoiceChangerPreset(ZegoVoiceChangerPreset preset) = 0;

    /// Setting up the specific voice changer parameters.
    ///
    /// Available since: 1.10.0
    /// Description: Call this function to set custom voice changer effect.
    /// Use cases: Often used in live broadcasting, voice chatroom and KTV.
    /// When to call: It needs to be called after [createEngine].
    /// Restrictions: Voice changer effect is only effective for SDK captured sound.
    /// Related APIs:
    /// [setVoiceChangerPreset] provide a set of preset voice changer effects.
    /// If you need advanced reverb/echo/voice changer effect, please use [setReverbAdvancedParam], [setReverbEchoParam], [setVoiceChangerParam] together.
    ///
    /// @param param Voice changer parameters.
    virtual void setVoiceChangerParam(ZegoVoiceChangerParam param) = 0;

    /// Setting up the reverberation via preset enumeration.
    ///
    /// Available since: 1.17.0
    /// Description: Call this function to set preset reverb effect.
    /// Use cases: Often used in live broadcasting, voice chatroom and KTV.
    /// When to call: It needs to be called after [createEngine]. Support call this function to change preset reverb effect during publishing stream.
    /// Restrictions: Reverb effect is only effective for SDK captured sound.
    /// Related APIs:
    /// If you need advanced reverb effect, please use [setReverbAdvancedParam].
    /// This function is mutually exclusive with [setVoiceChangerPreset]. If used at the same time, it will produce undefined effects.
    /// If you need advanced reverb/echo/voice changer effect, please use [setReverbAdvancedParam], [setReverbEchoParam], [setVoiceChangerParam] together.
    ///
    /// @param preset The reverberation preset enumeration.
    virtual void setReverbPreset(ZegoReverbPreset preset) = 0;

    /// Setting up the specific reverberation parameters.
    ///
    /// Available since: 1.10.0
    /// Description: Call this function to set preset reverb effect.
    /// Use cases: Often used in live broadcasting, voice chatroom and KTV.
    /// When to call: It needs to be called after [createEngine].
    /// Restrictions: Reverb effect is only effective for SDK captured sound.
    /// Caution: Different values dynamically set during publishing stream will take effect. When all parameters are set to 0, the reverberation is turned off.
    /// Related APIs:
    /// [setReverbPreset] provide a set of preset reverb effects.
    /// If you need advanced reverb/echo/voice changer effect, please use [setReverbAdvancedParam], [setReverbEchoParam], [setVoiceChangerParam] together.
    ///
    /// @param param Reverb advanced parameter.
    virtual void setReverbAdvancedParam(ZegoReverbAdvancedParam param) = 0;

    /// Setting up the specific reverberation echo parameters.
    ///
    /// Available since: 1.17.0
    /// Description: Call this function to set reverb echo effect. This function can be used with voice changer and reverb to achieve a variety of custom sound effects.
    /// Use cases: Often used in live broadcasting, voice chatroom and KTV.
    /// When to call: It needs to be called after [createEngine].
    /// Restrictions: Reverb echo effect is only effective for SDK captured sound.
    /// Related APIs: If you need advanced reverb/echo/voice changer effect, please use [setReverbAdvancedParam], [setReverbEchoParam], [setVoiceChangerParam] together.
    ///
    /// @param param The reverberation echo parameter.
    virtual void setReverbEchoParam(ZegoReverbEchoParam param) = 0;

    /// Enable or disable the virtual stereo effect when publishing stream..
    ///
    /// Available since: 1.10.0; Note: Starting from 2.15.0, the angle parameter supports setting -1 to present a all round virtual stereo effect.
    /// Description: Call this function to enable / disable the virtual stereo effect when publishing stream.
    /// Use cases: Often used in live broadcasting, voice chatroom and KTV.
    /// When to call: It needs to be called after [createEngine].
    /// Restrictions: Virtual stereo effect is only effective for SDK captured sound.
    /// Caution: You need to set up a dual channel with [setAudioConfig] for the virtual stereo to take effect.
    ///
    /// @param enable true to turn on the virtual stereo, false to turn off the virtual stereo.
    /// @param angle The angle of the sound source in virtual stereo in the range of -1 ~ 360, with 90 being directly in front, 0 / 180 / 270 corresponding to the rightmost and leftmost respectively. In particular, when set to -1, it is all round virtual stereo effects.
    virtual void enableVirtualStereo(bool enable, int angle) = 0;

    /// Enable or disable the virtual stereo effect when playing stream.
    ///
    /// Available since: 2.8.0
    /// Description: Call this function to enable/disable the virtual stereo effect when playing stream.
    /// Use cases: Often used in live broadcasting, voice chatroom and KTV.
    /// When to call: It needs to be called after [createEngine].
    /// Caution: It can dynamically switch and set angle parameters before and after playing stream. After stopping playing stream, it will automatically reset and disable.
    ///
    /// @param enable true to turn on the virtual stereo, false to turn off the virtual stereo.
    /// @param angle The angle of the sound source in virtual stereo in the range of 0 ~ 360, with 90 being directly in front, 0 / 180 / 270 corresponding to the rightmost and leftmost respectively.
    /// @param streamID Stream ID.
    virtual void enablePlayStreamVirtualStereo(bool enable, int angle,
                                               const std::string &streamID) = 0;

    /// Turn on or off the electronic sound effect.
    ///
    /// Available since: 2.13.0
    /// Description: Call this function to turn on or off the electronic sound effect.
    /// Use cases: Often used in live broadcasting, voice chatroom and sung unaccompanied scenes.
    /// Default value: When this function is not called, the electronic sound effect is not enabled by default.
    /// When to call: It needs to be called after [createEngine].
    /// Restrictions: None.
    /// Caution: When the mode parameter is Harmonic Minor, the tonal parameter does not take effect.
    /// Related APIs: Common electronic sound effect configurations can be set via [setVoiceChangerPreset].
    ///
    /// @param enable true to turn on the electronic sound effect, false to turn off the electronic sound effect.
    /// @param mode Mode of Electronic Effects reference.
    /// @param tonal The starting pitch of an electric tone in a given mode, representing 12 semitones in one octave of the sound, in the range [0, 11].
    virtual void setElectronicEffects(bool enable, ZegoElectronicEffectsMode mode, int tonal) = 0;

    /// Create the real time sequential data manager instance
    ///
    /// Available: since 2.14.0
    /// Description: Create a manager object for sending/receiving real-time signaling.
    /// Use cases: You can use this function when you need to use real-time signaling to implement services such as cloud games and remote desktops.
    /// When to call: After logging in to a room.
    /// Restrictions: Only one corresponding manager object can be created for each room ID of [loginRoom], that is, only one object can be created in single room mode, and multiple objects can be created in multi-room mode.
    /// Caution: If you create this object before using the audio and video function (push/pull streaming), the camera and microphone will be automatically closed. If the user has not called [enableCamera] / [enableAudioCaptureDevice] before the object is destroyed, it will be destroyed After this object, the SDK will automatically restore the camera and microphone.
    ///
    /// @param roomID Fill in the room ID that has been logged in, and all related stuff will be do in this room.
    /// @return The real-time sequential data manager instance, nullptr will be returned when the maximum number is exceeded.
    virtual IZegoRealTimeSequentialDataManager *
    createRealTimeSequentialDataManager(const std::string &roomID) = 0;

    /// Destroy the real time sequential data manager instance
    ///
    /// Available: since 2.14.0
    /// Description: Destroy the [ZegoRealTimeSequentialDataManager] instance object.
    /// Use cases: When you no longer need to use the real-time signaling function, you can use this function to destroy the instance object created by the [createRealTimeSequentialDataManager] function
    /// When to call: When you need to the real-time signaling manager object needs to be destroyed
    /// Restrictions: After destroy the instance, you need to release the [ZegoRealTimeSequentialDataManager] instance object you hold by yourself, and don’t call the function of this instance object after the destruction.
    /// Caution: If you have not called [enableCamera] / [enableAudioCaptureDevice] before this object is destroyed, the SDK will automatically restore (enable) the camera and microphone after the object is destroyed.
    ///
    /// @param manager The real time sequential data manager instance to be destroyed.
    virtual void
    destroyRealTimeSequentialDataManager(IZegoRealTimeSequentialDataManager *&manager) = 0;

    /// Sends a Broadcast Message.
    ///
    /// Available since: 1.2.1
    /// Description: Send a broadcast message to the room, users who have entered the same room can receive the message, and the message is reliable.
    /// Use cases: Generally used when the number of people in the live room does not exceed 500.
    /// When to call: After calling [loginRoom] to log in to the room.
    /// Restrictions: It is not supported when the number of people online in the room exceeds 500. If you need to increase the limit, please contact ZEGO technical support to apply for evaluation. The frequency of sending broadcast messages in the same room cannot be higher than 10 messages/s. The maximum QPS for a single user calling this interface from the client side is 2. For restrictions on the use of this function, please contact ZEGO technical support.
    /// Related callbacks: The room broadcast message can be received through [onIMRecvBroadcastMessage].
    /// Related APIs: Barrage messages can be sent through the [sendBarrageMessage] function, and custom command can be sent through the [sendCustomCommand] function.
    ///
    /// @param roomID Room ID. Required: Yes. Value range: The maximum length is 128 bytes. Caution: The room ID is in string format and only supports numbers, English characters and'~','!','@','#','$','%','^','&', ' *','(',')','_','+','=','-','`',';',''',',','.','<' ,'>','/','\'.
    /// @param message The content of the message. Required: Yes. Value range: The length does not exceed 1024 bytes.
    /// @param callback Send a notification of the result of a broadcast message. Required: No. Caution: Passing [nullptr] means not receiving callback notifications.
    virtual void sendBroadcastMessage(const std::string &roomID, const std::string &message,
                                      ZegoIMSendBroadcastMessageCallback callback) = 0;

    /// Sends a Barrage Message (bullet screen) to all users in the same room, without guaranteeing the delivery.
    ///
    /// Available since: 1.5.0
    /// Description: Send a barrage message to the room, users who have logged in to the same room can receive the message, the message is unreliable.
    /// Use cases: Generally used in scenarios where there is a large number of messages sent and received in the room and the reliability of the messages is not required, such as live barrage.
    /// When to call: After calling [loginRoom] to log in to the room.
    /// Restrictions: The frequency of sending barrage messages in the same room cannot be higher than 20 messages/s. For restrictions on the use of this function, please contact ZEGO technical support.
    /// Related callbacks: The room barrage message can be received through [onIMRecvBarrageMessage].
    /// Related APIs: Broadcast messages can be sent through the [sendBroadcastMessage] function, and custom command can be sent through the [sendCustomCommand] function.
    ///
    /// @param roomID Room ID. Required: Yes. Value range: The maximum length is 128 bytes. Caution: The room ID is in string format and only supports numbers, English characters and'~','!','@','#','$','%','^','&', ' *','(',')','_','+','=','-','`',';',''',',','.','<' ,'>','/','\'.
    /// @param message The content of the message. Required: Yes. Value range: The length does not exceed 1024 bytes.
    /// @param callback Send barrage message result callback.Required: No. Caution: Passing [nullptr] means not receiving callback notifications.
    virtual void sendBarrageMessage(const std::string &roomID, const std::string &message,
                                    ZegoIMSendBarrageMessageCallback callback) = 0;

    /// Sends a Custom Command to the specified users in the same room.
    ///
    /// Available since: 1.2.1
    /// Description: After calling this function, users in the same room who have entered the room can receive the message, the message is unreliable.
    /// Use cases: Generally used in scenarios where there is a large number of messages sent and received in the room and the reliability of the messages is not required, such as live barrage.
    /// When to call: After calling [loginRoom] to log in to the room.
    /// Restrictions: Generally used when the number of people in the live room does not exceed 500.The frequency of sending barrage messages in the same room cannot be higher than 20 messages/s. For restrictions on the use of this function, please contact ZEGO technical support.
    /// Related callbacks: The room custom command can be received through [onIMRecvCustomCommand].
    /// Related APIs: Broadcast messages can be sent through the [sendBroadcastMessage] function, and barrage messages can be sent through the [sendBarrageMessage] function.
    /// Privacy reminder: Please do not fill in sensitive user information in this interface, including but not limited to mobile phone number, ID number, passport number, real name, etc.
    ///
    /// @param roomID Room ID. Required: Yes. Value range: The maximum length is 128 bytes. Caution: The room ID is in string format and only supports numbers, English characters and'~','!','@','#','$','%','^','&', ' *','(',')','_','+','=','-','`',';',''',',','.','<' ,'>','/','\'.
    /// @param command Custom command content. Required: Yes. Value range: The maximum length is 1024 bytes. Caution: To protect privacy, please do not fill in sensitive user information in this interface, including but not limited to mobile phone number, ID number, passport number, real name, etc.
    /// @param toUserList List of recipients of signaling. Required: Yes. Value range: user list or [nullptr]. Caution: When it is [nullptr], the SDK will send custom signaling back to all users in the room
    /// @param callback Send a notification of the signaling result. Required: No. Caution: Passing [nullptr] means not receiving callback notifications.
    virtual void sendCustomCommand(const std::string &roomID, const std::string &command,
                                   std::vector<ZegoUser> toUserList,
                                   ZegoIMSendCustomCommandCallback callback) = 0;

    /// Creates a media player instance.
    ///
    /// Available since: 2.1.0
    /// Description: Creates a media player instance.
    /// Use case: It is often used to play media resource scenes, For example, play video files, push the video of media resources in combination with custom video acquisition, and the remote end can pull the stream for viewing.
    /// When to call: It can be called after the SDK by [createEngine] has been initialized.
    /// Restrictions: Currently, a maximum of 4 instances can be created, after which it will return nullptr.
    /// Caution: The more instances of a media player, the greater the performance overhead on the device.
    /// Related APIs: User can call [destroyMediaPlayer] function to destroy a media player instance.
    ///
    /// @return Media player instance, nullptr will be returned when the maximum number is exceeded.
    virtual IZegoMediaPlayer *createMediaPlayer() = 0;

    /// Destroys a media player instance.
    ///
    /// Available since: 2.1.0
    /// Description: Destroys a media player instance.
    /// Related APIs: User can call [createMediaPlayer] function to create a media player instance.
    ///
    /// @param mediaPlayer The media player instance object to be destroyed.
    virtual void destroyMediaPlayer(IZegoMediaPlayer *&mediaPlayer) = 0;

    /// Creates a audio effect player instance.
    ///
    /// Available since: 1.16.0
    /// Description: Creates a audio effect player instance.
    /// Use cases: When you need to play short sound effects, such as applause, cheers, etc., you can use audioEffectPlayer to achieve.
    /// When to call: It can be called after [createEngine].
    /// Restrictions: Currently, a maximum of 1 instances can be created, after which it will return nullptr.
    /// Related APIs: [destroyAudioEffectPlayer].
    ///
    /// @return audio effect player instance, nullptr will be returned when the maximum number is exceeded.
    virtual IZegoAudioEffectPlayer *createAudioEffectPlayer() = 0;

    /// Destroys a audio effect player instance.
    ///
    /// Available since: 1.16.0
    /// Description: Destroys the specified audio effect player instance.
    /// When to call: It can be called after [createAudioEffectPlayer].
    /// Restrictions: None.
    /// Related APIs: [createAudioEffectPlayer].
    ///
    /// @param audioEffectPlayer The audio effect player instance object to be destroyed.
    virtual void destroyAudioEffectPlayer(IZegoAudioEffectPlayer *&audioEffectPlayer) = 0;

    /// Creates a media data publisher instance.
    ///
    /// Available since: 2.17.0
    /// Description: Developers can use this interface to create ZegoMediaDataPublisher objects to push local media resource files to implement server-side streaming scenarios, such as AI classrooms.
    /// Use cases: Often used in server-side publishing stream scenarios, such as AI classrooms.
    /// When to call: After calling the [createEngine] function to create an engine.
    /// Caution: Currently, a maximum of 1 instance can be created, after which it will return nullptr.
    /// Note: This function is only available in ZegoExpressVideo SDK!
    ///
    /// @return Media data publisher instance, nullptr will be returned when the maximum number is exceeded.
    virtual IZegoMediaDataPublisher *createMediaDataPublisher() = 0;

    /// Destroys a media data publisher instance.
    ///
    /// Available since: 2.17.0
    /// Description: Destroys a media data publisher instance.
    /// Use cases: Often used in server-side publishing stream scenarios, such as AI classrooms.
    /// When to call: After calling the [createEngine] function to create an engine.
    /// Note: This function is only available in ZegoExpressVideo SDK!
    ///
    /// @param mediaDataPublisher The media data publisher instance object to be destroyed
    virtual void destroyMediaDataPublisher(IZegoMediaDataPublisher *&mediaDataPublisher) = 0;

    /// Starts to record and directly save the data to a file.
    ///
    /// Available since: 1.10.0
    /// Description: Starts to record locally captured audio or video and directly save the data to a file, The recorded data will be the same as the data publishing through the specified channel.
    /// When to call: This function needs to be called after the success of [startPreview] or [startPublishingStream] to be effective.
    /// Restrictions: None.
    /// Caution: Developers should not [stopPreview] or [stopPublishingStream] during recording, otherwise the SDK will end the current recording task. The data of the media player needs to be mixed into the publishing stream to be recorded.
    /// Related callbacks: Developers will receive the [onCapturedDataRecordStateUpdate] and the [onCapturedDataRecordProgressUpdate] callback after start recording.
    ///
    /// @param config Record config.
    /// @param channel Publishing stream channel.
    virtual void
    startRecordingCapturedData(ZegoDataRecordConfig config,
                               ZegoPublishChannel channel = ZEGO_PUBLISH_CHANNEL_MAIN) = 0;

    /// Stops recording locally captured audio or video.
    ///
    /// Available since: 1.10.0
    /// Description: Stops recording locally captured audio or video.
    /// When to call: After [startRecordingCapturedData].
    /// Restrictions: None.
    ///
    /// @param channel Publishing stream channel.
    virtual void
    stopRecordingCapturedData(ZegoPublishChannel channel = ZEGO_PUBLISH_CHANNEL_MAIN) = 0;

    /// Sets up the event callback handler for data recording.
    ///
    /// Available since: 1.10.0
    /// Description: Implemente the functions of ZegoDataRecordEventHandler to get notified when recode state and process changed.
    /// When to call: After [createEngine].
    /// Restrictions: None.
    ///
    /// @param eventHandler Data record event handler.
    virtual void
    setDataRecordEventHandler(std::shared_ptr<IZegoDataRecordEventHandler> eventHandler) = 0;

    /// Start system performance monitoring.
    ///
    /// Available since: 1.19.0
    /// Description: Start system performance monitoring, monitor system or App's CPU usage and memory usage. Support set the monitoring interval.
    /// Use cases: Monitor system performance can help user quickly locate and solve performance problems and improve user experience.
    /// When to call: It needs to be called after [createEngine].
    /// Restrictions: None.
    /// Related callbacks: After starting monitoring, you can receive system performance status via [onPerformanceStatusUpdate] callback. [onPerformanceStatusUpdate] callback notification period is the value set by millisecond parameter.
    /// Related APIs: Call [stopPerformanceMonitor] to stop system performance monitoring.
    ///
    /// @param millisecond Monitoring time period(in milliseconds), the value range is [1000, 10000]. Default value is 2000 ms.
    virtual void startPerformanceMonitor(unsigned int millisecond = 2000) = 0;

    /// Stop system performance monitoring.
    ///
    /// Available since: 1.19.0
    /// Description: Stop system performance monitoring. After the monitoring is stopped, the [onPerformanceStatusUpdate] callback will not triggered.
    /// Use cases: Monitor system performance can help user quickly locate and solve performance problems and improve user experience.
    /// When to call: It needs to be called after [createEngine].
    /// Restrictions: None.
    /// Related APIs: Call [startPerformanceMonitor] to start system performance monitoring.
    virtual void stopPerformanceMonitor() = 0;

    /// Start network probe.
    ///
    /// Available since: 2.3.0
    /// Description: Some local network problems may cause audio and video calls to fail. Using this function to probe the network protocols, assist in locating and solving related network problems.
    /// Use cases: Before pushing and pulling the stream, detect and locate some possible network problems.
    /// When to call: It needs to be called after [createEngine].
    /// Restrictions: The SDK will not perform multiple network probe at the same time, that is, if the network probe is in progress, the SDK will ignore subsequent calls of this function.
    /// Caution: The SDK detects http, tcp, and udp in sequence internally. If the probe fails in the middle, the subsequent detection will not continue. Therefore, when reading the values ​​in the probe result, please pay attention to check if the value is nullptr. Network probe may take a long time. Developers can call [stopNetworkProbe] to stop network probe if needed. It is not recommended to start network probe during publishing/playing stream.
    /// Related APIs: Call [stopNetworkProbe] to stop network probe.
    ///
    /// @param config network probe config.
    /// @param callback Network probe result callback.
    virtual void startNetworkProbe(ZegoNetworkProbeConfig config,
                                   ZegoNetworkProbeResultCallback callback) = 0;

    /// Stop network probe.
    ///
    /// Available since: 2.3.0
    /// Description: Stop network probe.
    /// Use cases: Before pushing and pulling the stream, detect and locate some possible network problems.
    /// When to call: It needs to be called after [createEngine].
    /// Restrictions: None.
    /// Related APIs: Call [startNetworkProbe] to start network probe.
    virtual void stopNetworkProbe() = 0;

    /// Start network speed test. Support set speed test interval。
    ///
    /// Available since: 1.20.0
    /// Description: This function supports uplink/downlink network speed test.
    /// Use cases: This function can be used to detect whether the network environment is suitable for pushing/pulling streams with specified bitrates.
    /// When to call: It needs to be called after [loginRoom], and before [startPublishingStream]. If you call [startPublishingStream] while speed testing, the speed test will automatically stop.
    /// Restrictions: The maximum allowable test time for a single network speed test is 3 minutes.
    /// Caution: Developers can register [onNetworkSpeedTestQualityUpdate] callback to get the speed test result, which will be triggered every 3 seconds. If an error occurs during the speed test process, [onNetworkSpeedTestError] callback will be triggered. If this function is repeatedly called multiple times, the last functioh call's configuration will be used.
    /// Related APIs: Call [stopNetworkSpeedTest] to stop network speed test.
    ///
    /// @param config Network speed test configuration.
    /// @param interval Interval of network speed test. In milliseconds, default is 3000 ms.
    virtual void startNetworkSpeedTest(ZegoNetworkSpeedTestConfig config,
                                       unsigned int interval = 3000) = 0;

    /// Stop network speed test.
    ///
    /// Available since: 1.20.0
    /// Description: Stop network speed test.
    /// Use cases: This function can be used to detect whether the network environment is suitable for pushing/pulling streams with specified bitrates.
    /// When to call: It needs to be called after [createEngine].
    /// Restrictions: None.
    /// Caution: After the network speed test stopped, [onNetworkSpeedTestQualityUpdate] callback will not be triggered.
    /// Related APIs: Call [startNetworkSpeedTest] to start network speed test.
    virtual void stopNetworkSpeedTest() = 0;

    /// Obtain synchronization network time information.
    ///
    /// Available since: 2.9.0
    /// Description: Obtain synchronization network time(NTP), including timestamp and maximum deviation.
    /// Use cases: When performing multi-terminal synchronization behaviors, network time synchronization is required.
    /// When to call: It needs to be called after [createEngine].
    /// Restrictions: None.
    virtual ZegoNetworkTimeInfo getNetworkTimeInfo() = 0;

    /// Enables or disables custom video rendering.
    ///
    /// Available since: 1.9.0
    /// Description: When enable is `true`,video custom rendering is enabled; if the value of `false`, video custom rendering is disabled.
    /// Use case: Use beauty features or apps that use a cross-platform interface framework (for example, Qt requires a complex hierarchical interface to achieve high-experience interaction) or game engines (for example, Unity3D, Cocos2d-x), etc.
    /// Default value: Custom video rendering is turned off by default when this function is not called.
    /// When to call: Must be set after [createEngine] before the engine starts, before calling [startPreview], [startPublishingStream],[startPlayingStream], [createRealTimeSequentialDataManager].The configuration can only be modified after the engine is stopped, that is, after [logoutRoom] is called.
    /// Caution: Custom video rendering can be used in conjunction with custom video capture, but when both are enabled, the local capture frame callback for custom video rendering will no longer be triggered, and the developer should directly capture the captured video frame from the custom video capture source.
    /// Related callbacks: When developers to open a custom rendering, by calling [setCustomVideoRenderHandler] can be set up to receive local and remote video data to be used for custom rendering. [onCapturedVideoFrameRawData] local bare preview video frame data correction, distal pull flow [onRemoteVideoFrameRawData] naked video frame data correction.
    /// Note: This function is only available in ZegoExpressVideo SDK!
    ///
    /// @param enable enable or disable
    /// @param config custom video render config
    virtual void enableCustomVideoRender(bool enable, ZegoCustomVideoRenderConfig *config) = 0;

    /// Sets up the event callback handler for custom video rendering.
    ///
    /// Available since: 1.9.0
    /// Description: Custom video rendering, where the developer is responsible for rendering the video data onto the UI components. With the change callback set, a callback that throws video data to the developer will be triggered when the developer calls startPreview, startPublishingStream, and startPlayingStream.
    /// Use case: Use the beauty function, or the App uses a cross-platform interface framework (e.g. Qt requires a complex hierarchical interface to achieve high-experience interaction) or a game engine (e.g. Unity3D, Cocos2D-X).
    /// When to call: after [createEngine].
    /// Related callbacks: [onCapturedVideoFrameRawData] local bare preview video frame data correction, distal pull flow [onRemoteVideoFrameRawData] naked video frame data correction.
    /// Note: This function is only available in ZegoExpressVideo SDK!
    ///
    /// @param handler Custom video render handler
    virtual void
    setCustomVideoRenderHandler(std::shared_ptr<IZegoCustomVideoRenderHandler> handler) = 0;

    /// Enables or disables custom video capture (for the specified channel).
    ///
    /// Available since: 1.9.0
    /// Description: If the value of enable is true, the video collection function is enabled. If the value of enable is false, the video collection function is disabled.
    /// Use case: The App developed by the developer uses the beauty SDK of a third-party beauty manufacturer to broadcast non-camera collected data.
    /// Default value: When this function is not called, custom video collection is disabled by default.
    /// When to call: After [createEngine], call [startPreview], [startPublishingStream], [createRealTimeSequentialDataManager], and call [logoutRoom] to modify the configuration.
    /// Caution: Custom video rendering can be used in conjunction with custom video capture, but when both are enabled, the local capture frame callback for custom video rendering will no longer be triggered, and the developer should directly capture the captured video frame from the custom video capture source.
    /// Related callbacks: When developers to open a custom collection, by calling [setCustomVideoCaptureHandler] can be set up to receive a custom collection start-stop event notification.
    /// Note: This function is only available in ZegoExpressVideo SDK!
    ///
    /// @param enable enable or disable
    /// @param config custom video capture config
    /// @param channel publish channel
    virtual void
    enableCustomVideoCapture(bool enable, ZegoCustomVideoCaptureConfig *config,
                             ZegoPublishChannel channel = ZEGO_PUBLISH_CHANNEL_MAIN) = 0;

    /// Sets the event callback handler for custom video capture.
    ///
    /// Available since: 1.9.0
    /// Description: Example Set the callback for custom video capture. That is, the developer is responsible for collecting video data, and sends the collected video data to the SDK for coding and pushing the video data to the ZEGO RTC server.
    /// Use case: This feature is typically used by developers using third-party beauty features or livestreaming of games.
    /// When to call: After [createEngine] .
    /// Caution: In the case of customized video collection, the SDK will not start the camera to collect video data, and developers need to collect video data from the video collection source. A callback notifying the developer that it can start sending video data is triggered when the developer calls [startPreview] to start pushing the stream to [startPublishingStream]. A callback notifying the developer that it can stop sending video data is triggered when [stopPreview] and [stopPublishingStream].
    /// Related callbacks: [onStart] Starts collection, and [onStop] stops collection.
    /// Note: This function is only available in ZegoExpressVideo SDK!
    ///
    /// @param handler Custom video capture handler
    virtual void
    setCustomVideoCaptureHandler(std::shared_ptr<IZegoCustomVideoCaptureHandler> handler) = 0;

    /// Sends the video frames (Raw Data) produced by custom video capture to the SDK (for the specified channel).
    ///
    /// Available since: 1.9.0
    /// Description: Sends customized raw video frame data to the SDK.
    /// When to call: After receiving the [onStart] notification, the developer starts the call after the collection logic starts and ends the call after the [onStop] notification.
    /// Caution: This interface must be called with [enableCustomVideoCapture] passing the parameter type RAW_DATA.
    /// Related APIs: [enableCustomVideoCapture], [setCustomVideoCaptureHandler].
    /// Note: This function is only available in ZegoExpressVideo SDK!
    ///
    /// @param data video frame data
    /// @param dataLength video frame data length
    /// @param params video frame param
    /// @param referenceTimeMillisecond video frame reference time, UNIX timestamp, in milliseconds.
    /// @param channel Publishing stream channel
    virtual void
    sendCustomVideoCaptureRawData(const unsigned char *data, unsigned int dataLength,
                                  ZegoVideoFrameParam params,
                                  unsigned long long referenceTimeMillisecond,
                                  ZegoPublishChannel channel = ZEGO_PUBLISH_CHANNEL_MAIN) = 0;

    /// Sends the video frames (Encoded Data) produced by custom video capture to the SDK (for the specified channel).
    ///
    /// Available since: 1.9.0
    /// Description: Send custom captured video frame type CVPixelBuffer data to the SDK.
    /// When to call: After receiving the [onStart] notification, the developer starts the call after the collection logic starts and ends the call after the [onStop] notification.
    /// Caution: It is recommended to make a GOP every 2s, and each I frame must carry SPS and PPS and be placed at the top.  Only I and P frames are accepted, B frames are NOT accepted. Calling this interface must be [enableCustomVideoCapture] with an argument of type ZegoVideoBufferTypeEncodedData.
    /// Related APIs: [enableCustomVideoCapture], [setCustomVideoCaptureHandler].
    /// Note: This function is only available in ZegoExpressVideo SDK!
    ///
    /// @param data video frame encoded data
    /// @param dataLength video frame data length
    /// @param params video frame param
    /// @param referenceTimeMillisecond video frame reference time, UNIX timestamp, in milliseconds.
    /// @param channel Publishing stream channel
    virtual void
    sendCustomVideoCaptureEncodedData(const unsigned char *data, unsigned int dataLength,
                                      ZegoVideoEncodedFrameParam params,
                                      unsigned long long referenceTimeMillisecond,
                                      ZegoPublishChannel channel = ZEGO_PUBLISH_CHANNEL_MAIN) = 0;

    /// Sets the video fill mode of custom video capture (for the specified channel).
    ///
    /// Available since: 1.10.0
    /// Use cases: If the customized collection resolution and SDK coding resolution are inconsistent, THE SDK will process the video frame according to the fill mode and adjust it to the coding resolution.
    /// Description: When the custom video collection function is enabled, you can use this interface to set the video zooming and filling mode.
    /// When to call: Before [sendCustomVideoCaptureRawData], [sendCustomVideoCaptureTextureData], [sendCustomVideoCapturePixelBuffer], [sendCustomVideoCaptureEncodedData].
    /// Note: This function is only available in ZegoExpressVideo SDK!
    ///
    /// @param mode View mode
    /// @param channel Publishing stream channel
    virtual void
    setCustomVideoCaptureFillMode(ZegoViewMode mode,
                                  ZegoPublishChannel channel = ZEGO_PUBLISH_CHANNEL_MAIN) = 0;

    /// Sets device state of custom video capture (for the specified channel).
    ///
    /// Available since: 2.15.0.
    /// Description: User can set the video device state of custom video capture (for the specified channel) through this function.
    /// When to call: After the callback [onStart] is received.
    /// Restrictions: None.
    /// Related Callbacks: The remote user that play stream of local user publishing stream can receive state update notification by monitoring [onRemoteCameraStateUpdate] callbacks.
    /// Note: This function is only available in ZegoExpressVideo SDK!
    ///
    /// @param isEnable Whether the device is enable.
    /// @param state The device state.
    /// @param channel Publishing stream channel
    virtual void
    setCustomVideoCaptureDeviceState(bool isEnable, ZegoRemoteDeviceState state,
                                     ZegoPublishChannel channel = ZEGO_PUBLISH_CHANNEL_MAIN) = 0;

    /// Set the region of interest (ROI) for encoder of custom video capture (for the specified channel).
    ///
    /// Available since: 2.16.0.
    /// Description: You can set the video encoder's region of interest rectangle areas of custom video capture (for the specified channel) through this function.
    /// When to call: After the callback [onStart] is received.
    /// Restrictions: Currently, only certain video encoders support this function, please contact ZEGO technical support before using it.
    /// Caution: This function is currently an experimental feature, please contact ZEGO technical support before using it.
    /// Note: This function is only available in ZegoExpressVideo SDK!
    ///
    /// @param rectList ROI rectangle area list, currently supports up to 6 areas.
    /// @param channel Publish channel
    virtual void setCustomVideoCaptureRegionOfInterest(
        std::vector<ZegoRoiRect> rectList,
        ZegoPublishChannel channel = ZEGO_PUBLISH_CHANNEL_MAIN) = 0;

    /// Enables or disables custom video processing.
    ///
    /// Available since: 2.2.0 (Android/iOS/macOS native), 2.4.0 (Windows/macOS C++).
    /// Description: When the developer opens custom pre-processing, by calling [setCustomVideoProcessHandler] you can set the custom video pre-processing callback.
    /// Use cases: After the developer collects the video data by himself or obtains the video data collected by the SDK, if the basic beauty and watermark functions of the SDK cannot meet the needs of the developer (for example, the beauty effect cannot meet the expectations), the ZegoEffects SDK can be used to perform the video Some special processing, such as beautifying, adding pendants, etc., this process is the pre-processing of custom video.
    /// Default value: Off by default
    /// When to call: Must be set before calling [startPreview], [startPublishingStream], [createRealTimeSequentialDataManager]. If you need to modify the configuration, please call [logoutRoom] to log out of the room first, otherwise it will not take effect.
    /// Restrictions: None.
    /// Related APIs: Call the [setCustomVideoProcessHandler] function to set the callback before custom video processing.
    /// Note: This function is only available in ZegoExpressVideo SDK!
    ///
    /// @param enable enable or disable. Required: Yes.
    /// @param config custom video processing configuration. Required: Yes.Caution: If NULL is passed, the platform default value is used.
    /// @param channel Publishing stream channel.Required: No.Default value: Main publish channel.
    virtual void
    enableCustomVideoProcessing(bool enable, ZegoCustomVideoProcessConfig *config,
                                ZegoPublishChannel channel = ZEGO_PUBLISH_CHANNEL_MAIN) = 0;

    /// Sets up the event callback handler for custom video processing.
    ///
    /// Available since: 2.2.0 (Android/iOS/macOS native), 2.4.0 (Windows/macOS C++).
    /// Description: When the developer opens the custom pre-processing, by calling [setCustomVideoProcessHandler], you can set the custom video pre-processing callback to obtain the original video data.
    /// Use cases: After the developer collects the video data by himself or obtains the video data collected by the SDK, if the basic beauty and watermark functions of the SDK cannot meet the needs of the developer (for example, the beauty effect cannot meet the expectations), the ZegoEffects SDK can be used to perform the video Some special processing, such as beautifying, adding pendants, etc., this process is the pre-processing of custom video.
    /// When to call: Called before [startPreview], [startPublishingStream] and [createRealTimeSequentialDataManager], otherwise it may cause the timing of obtaining video data to be too slow.
    /// Restrictions: None.
    /// Related APIs: Call [enableCustomVideoProcessing] function to enable custom video pre-processing callback.
    /// Note: This function is only available in ZegoExpressVideo SDK!
    ///
    /// @param handler Custom video process handler.Required: Yes.
    virtual void
    setCustomVideoProcessHandler(std::shared_ptr<IZegoCustomVideoProcessHandler> handler) = 0;

    /// Send the original video data after the pre-processing of the custom video to the SDK, and support other channels to push the stream.
    ///
    /// Available since: 2.4.0
    /// Description: When the developer opens the custom pre-processing, by calling [setCustomVideoProcessHandler], you can set the custom video pre-processing callback to obtain the original video data.
    /// Use cases: After the developer collects the video data by himself or obtains the video data collected by the SDK, if the basic beauty and watermark functions of the SDK cannot meet the needs of the developer (for example, the beauty effect cannot meet the expectations), the ZegoEffects SDK can be used to perform the video Some special processing, such as beautifying, adding pendants, etc., this process is the pre-processing of custom video.
    /// When to call: Must be called in the [onCapturedUnprocessedCVPixelbuffer] callback.
    /// Restrictions: None.
    /// Platform differences: Only valid on Windows platform.
    /// Note: This function is only available in ZegoExpressVideo SDK!
    ///
    /// @param data Raw video data. RGB format data storage location is data[0], YUV format data storage location is Y component：data[0], U component：data[1], V component：data[2].
    /// @param dataLength Raw video data length. RGB format data length storage location is dataLength[0], YUV format data storage location respectively Y component length：dataLength[0], U component length：dataLength[1], V component length：dataLength[2].
    /// @param params video frame param.
    /// @param referenceTimeMillisecond video frame reference time, UNIX timestamp, in milliseconds.
    /// @param channel Publishing stream channel.Required: No.Default value: Main publish channel.
    virtual void
    sendCustomVideoProcessedRawData(const unsigned char **data, unsigned int *dataLength,
                                    ZegoVideoFrameParam params,
                                    unsigned long long referenceTimeMillisecond,
                                    ZegoPublishChannel channel = ZEGO_PUBLISH_CHANNEL_MAIN) = 0;

    /// Send the [CVPixelBuffer] type video data after the custom video processing to the SDK (for the specified channel).
    ///
    /// Available since: 2.2.0 (iOS native), 2.4.0 (macOS C++).
    /// Description: When the custom video pre-processing is turned on, the [CVPixelBuffer] format video data after the custom video pre-processing is sent to the SDK, and other channels are supported.
    /// Use cases: After the developer collects the video data by himself or obtains the video data collected by the SDK, if the basic beauty and watermark functions of the SDK cannot meet the needs of the developer (for example, the beauty effect cannot meet the expectations), the ZegoEffects SDK can be used to perform the video Some special processing, such as beautifying, adding pendants, etc., this process is the pre-processing of custom video.
    /// When to call: Must be called in the [onCapturedUnprocessedCVPixelbuffer] callback.
    /// Restrictions: This interface takes effect when [enableCustomVideoProcessing] is called to enable custom video pre-processing and the bufferType of config is passed in [ZegoVideoBufferTypeCVPixelBuffer].
    /// Platform differences: Only valid on Windows platform.
    /// Note: This function is only available in ZegoExpressVideo SDK!
    ///
    /// @param buffer CVPixelBuffer type video frame data to be sent to the SDK.
    /// @param timestamp Timestamp of this video frame.
    /// @param channel Publishing stream channel.
    virtual void sendCustomVideoProcessedCVPixelBuffer(
        void *buffer, unsigned long long timestamp,
        ZegoPublishChannel channel = ZEGO_PUBLISH_CHANNEL_MAIN) = 0;

    /// Enable local collection and custom audio processing(before ear return).
    ///
    /// Available since: 1.13.0
    /// Description: Enable custom audio processing(before ear return), developers can receive locally collected audio frames through [onProcessCapturedAudioData], and can modify the audio data.
    /// Use cases: If the developer wants to implement special functions (such as voice change, bel canto, etc.) through custom processing after the audio data is collected or before the remote audio data is drawn for rendering.
    /// When to call: It needs to be called before [startPublishingStream], [startPlayingStream], [startPreview], [createMediaPlayer], [createAudioEffectPlayer] and [createRealTimeSequentialDataManager] to be effective.
    /// Restrictions: None.
    ///
    /// @param enable Whether to enable local capture custom audio processing.
    /// @param config Custom audio processing configuration.
    virtual void enableCustomAudioCaptureProcessing(bool enable,
                                                    ZegoCustomAudioProcessConfig *config) = 0;

    /// Turn on local collection and custom audio processing (after ear return).
    ///
    /// Available since: 1.13.0
    /// Description: Enable custom audio processing(after ear return), developers can receive locally collected audio frames through [onProcessCapturedAudioData], and can modify the audio data.
    /// Use cases: If the developer wants to implement special functions (such as voice change, bel canto, etc.) through custom processing after the audio data is collected or before the remote audio data is drawn for rendering.
    /// When to call: It needs to be called before [startPublishingStream], [startPlayingStream], [startPreview], [createMediaPlayer], [createAudioEffectPlayer] and [createRealTimeSequentialDataManager] to be effective.
    /// Restrictions: None.
    ///
    /// @param enable Whether to enable local capture custom audio processing.
    /// @param config Custom audio processing configuration.
    virtual void enableCustomAudioCaptureProcessingAfterHeadphoneMonitor(
        bool enable, ZegoCustomAudioProcessConfig *config) = 0;

    /// Enable custom audio processing for remote playing stream.
    ///
    /// Available since: 1.13.0
    /// Description: Enable remote streaming custom audio processing, developers can receive remote streaming audio frames through [onProcessRemoteAudioData], and can modify the audio data.
    /// Use cases: If the developer wants to implement special functions (such as voice change, bel canto, etc.) through custom processing before pulling the remote audio data for rendering.
    /// When to call: It needs to be called before [startPublishingStream], [startPlayingStream], [startPreview], [createMediaPlayer], [createAudioEffectPlayer] and [createRealTimeSequentialDataManager] to be effective.
    /// Restrictions: None.
    ///
    /// @param enable Whether to enable custom audio processing for remote playing stream.
    /// @param config Custom audio processing configuration.
    virtual void enableCustomAudioRemoteProcessing(bool enable,
                                                   ZegoCustomAudioProcessConfig *config) = 0;

    /// Enable custom audio processing for SDK playback audio data.
    ///
    /// Available since: 1.13.0
    /// Description: Enable remote streaming custom audio processing, developers can receive remote streaming audio frames through [onProcessRemoteAudioData], and can modify the audio data.
    /// Use cases: If the developer wants to implement special functions (such as voice change, bel canto, etc.) through custom processing after collecting audio data.
    /// When to call: It needs to be called before [startPublishingStream], [startPlayingStream], [startPreview], [createMediaPlayer], [createAudioEffectPlayer] and [createRealTimeSequentialDataManager] to be effective.
    /// Restrictions: None.
    ///
    /// @param enable Whether to enable custom audio processing for SDK playback audio data.
    /// @param config Custom audio processing configuration.
    virtual void enableCustomAudioPlaybackProcessing(bool enable,
                                                     ZegoCustomAudioProcessConfig *config) = 0;

    /// Set up callback handler for custom audio processing.
    ///
    /// Available since: 1.13.0
    /// Description: When the custom audio processing is enabled, the custom audio processing callback is set through this function, and the developer can modify the processed audio frame data in the callback.
    /// Use cases: If the developer wants to implement special functions (such as voice change, bel canto, etc.) through custom processing after the audio data is collected or before the remote audio data is drawn for rendering.
    /// When to call: After creating the engine.
    /// Restrictions: None.
    ///
    /// @param handler Callback handler for custom audio processing.
    virtual void
    setCustomAudioProcessHandler(std::shared_ptr<IZegoCustomAudioProcessHandler> handler) = 0;

    /// Enable audio data observering.
    ///
    /// Available since: 1.1.0
    /// Description: When custom audio processing is turned on, use this function to turn on audio data callback monitoring.
    /// Use cases: When develop need to monitor the original audio.
    /// When to call: After creating the engine.
    /// Restrictions: None.
    ///
    /// @param observerBitMask The callback function bitmask marker for receive audio data, refer to enum [ZegoAudioDataCallbackBitMask], when this param converted to binary, 0b01 that means 1 << 0 for triggering [onCapturedAudioData], 0x10 that means 1 << 1 for triggering [onPlaybackAudioData], 0x100 that means 1 << 2 for triggering [onMixedAudioData], 0x1000 that means 1 << 3 for triggering [onPlayerAudioData]. The masks can be combined to allow different callbacks to be triggered simultaneously.
    /// @param param param of audio frame.
    virtual void startAudioDataObserver(unsigned int observerBitMask,
                                        ZegoAudioFrameParam param) = 0;

    /// Disable audio data observering.
    ///
    /// Available since: 1.1.0
    /// Description: Disable audio data observering.
    /// Use cases: When develop need to monitor the original audio.
    /// When to call: After calling [startAudioDataObserver] to start audio data monitoring.
    virtual void stopAudioDataObserver() = 0;

    /// Sets up the event callback handler for receiving audio data.
    ///
    /// Available since: 1.1.0
    /// Description: This function can be called to receive audio data thrown by SDK bypass.
    /// Use cases: When the developer needs to obtain the audio data of the remote user or the data collected by the local microphone for other purposes (such as pure audio recording, pure audio third-party monitoring, pure audio real-time analysis).
    /// When to call: After creating the engine.
    /// Restrictions: The set callback needs to be effective after calling [startAudioDataObserver] and is in the push or pull state.
    /// Related APIs: Turn on the audio data monitoring call [startAudioDataObserver], turn off the audio data monitoring call [stopAudioDataObserver].
    /// Caution: The format of the thrown audio data is pcm. The SDK still controls the collection and playback of the sound device. This function is to copy a copy of the data collected or played inside the SDK for use by the developer.
    ///
    /// @param handler Audio data handler for receive audio data.
    virtual void setAudioDataHandler(std::shared_ptr<IZegoAudioDataHandler> handler) = 0;

    /// Enables the custom audio I/O function (for the specified channel), support PCM, AAC format data.
    ///
    /// Available since: 1.10.0
    /// Description: Enable custom audio IO function, support PCM, AAC format data.
    /// Use cases: If the developer wants to implement special functions (such as voice change, bel canto, etc.) through custom processing after the audio data is collected or before the remote audio data is drawn for rendering.
    /// When to call: It needs to be called before [startPublishingStream], [startPlayingStream], [startPreview], [createMediaPlayer], [createAudioEffectPlayer] and [createRealTimeSequentialDataManager] to be effective.
    /// Restrictions: None.
    ///
    /// @param enable Whether to enable custom audio IO, default is false.
    /// @param config Custom audio IO config.
    /// @param channel Specify the publish channel to enable custom audio IO.
    virtual void enableCustomAudioIO(bool enable, ZegoCustomAudioConfig *config,
                                     ZegoPublishChannel channel = ZEGO_PUBLISH_CHANNEL_MAIN) = 0;

    /// Sends AAC audio data produced by custom audio capture to the SDK (for the specified channel).
    ///
    /// Available since: 2.20.0
    /// Description: Sends the captured audio AAC data to the SDK.
    /// Use cases: The customer needs to obtain input after acquisition from the existing audio stream, audio file, or customized acquisition system, and hand it over to the SDK for transmission.
    /// When to call: After [enableCustomAudioIO] and publishing stream successfully.
    /// Restrictions: None.
    /// Related APIs: Enable the custom audio IO function [enableCustomAudioIO], and start the push stream [startPublishingStream].
    ///
    /// @param data AAC buffer data.
    /// @param dataLength The total length of the buffer data.
    /// @param configLength The length of AAC specific config (Note: The AAC encoded data length is 'encodedLength = dataLength - configLength').Value range: [0,64]
    /// @param referenceTimeMillisecond The UNIX timestamp of this AAC audio frame in millisecond.
    /// @param samples The number of samples for this AAC audio frame.Value range: [480,512,1024,1960,2048].
    /// @param param The param of this AAC audio frame.
    /// @param channel Publish channel for capturing audio frames.
    virtual void sendCustomAudioCaptureAACData(
        unsigned char *data, unsigned int dataLength, unsigned int configLength,
        unsigned long long referenceTimeMillisecond, unsigned int samples,
        ZegoAudioFrameParam param, ZegoPublishChannel channel = ZEGO_PUBLISH_CHANNEL_MAIN) = 0;

    /// Sends PCM audio data produced by custom audio capture to the SDK (for the specified channel).
    ///
    /// Available since: 1.10.0
    /// Description: Sends the captured audio PCM data to the SDK.
    /// Use cases: 1.The customer needs to obtain input after acquisition from the existing audio stream, audio file, or customized acquisition system, and hand it over to the SDK for transmission. 2.Customers have their own requirements for special sound processing for PCM input sources. After the sound processing, the input will be sent to the SDK for transmission.
    /// When to call: After [enableCustomAudioIO] and publishing stream successfully.
    /// Restrictions: None.
    /// Related APIs: Enable the custom audio IO function [enableCustomAudioIO], and start the push stream [startPublishingStream].
    ///
    /// @param data PCM buffer data.
    /// @param dataLength The total length of the buffer data.
    /// @param param The param of this PCM audio frame.
    /// @param channel Publish channel for capturing audio frames.
    virtual void
    sendCustomAudioCapturePCMData(unsigned char *data, unsigned int dataLength,
                                  ZegoAudioFrameParam param,
                                  ZegoPublishChannel channel = ZEGO_PUBLISH_CHANNEL_MAIN) = 0;

    /// Fetches PCM audio data of the remote stream from the SDK for custom audio rendering.
    ///
    /// Available since: 1.10.0
    /// Description: Fetches PCM audio data of the remote stream from the SDK for custom audio rendering, it is recommended to use the system framework to periodically invoke this function to drive audio data rendering.
    /// Use cases: When developers have their own rendering requirements, such as special applications or processing and rendering of the original PCM data that are pulled, it is recommended to use the custom audio rendering function of the SDK.
    /// When to call: After [enableCustomAudioIO] and playing stream successfully.
    /// Restrictions: None.
    /// Related APIs: Enable the custom audio IO function [enableCustomAudioIO], and start the play stream [startPlayingStream].
    ///
    /// @param data A block of memory for storing audio PCM data that requires user to manage the memory block's lifecycle, the SDK will copy the audio frame rendering data to this memory block.
    /// @param dataLength The length of the audio data to be fetch this time (dataLength = duration * sampleRate * channels * 2(16 bit depth i.e. 2 Btye)).
    /// @param param Specify the parameters of the fetched audio frame. sampleRate in ZegoAudioFrameParam must assignment
    virtual void fetchCustomAudioRenderPCMData(unsigned char *data, unsigned int dataLength,
                                               ZegoAudioFrameParam param) = 0;

    /// Creates a range audio instance.
    ///
    /// Available since: 2.11.0
    /// Description: Creates a range audio instance.
    /// Use case: Often used in game voice scenarios, users can use related functions by creating range audio instance objects.
    /// When to call: It can be called after the engine by [createEngine] has been initialized.
    /// Restrictions: Currently, a maximum of 1 instances can be created, after which it will return nullptr.
    /// Impacts on other APIs: If you use the range audio module, you cannot use the basic push-pull stream [startPublishingStream], [startPlayingStream] interfaces and related callbacks.
    ///
    /// @return range audio instance, nullptr will be returned when the maximum number is exceeded.
    virtual IZegoRangeAudio *createRangeAudio() = 0;

    /// Destroys a range audio instance.
    ///
    /// Available since: 2.11.0
    /// Description: Destroys a range audio instance.
    ///
    /// @param rangeAudio The range audio instance object to be destroyed.
    virtual void destroyRangeAudio(IZegoRangeAudio *&rangeAudio) = 0;

    /// Creates a copyrighted music instance.
    ///
    /// Available since: 2.13.0
    /// Description: Creates a copyrighted music instance.
    /// Use case: Often used in online KTV chorus scenarios, users can use related functions by creating copyrighted music instance objects.
    /// When to call: It can be called after the engine by [createEngine] has been initialized.
    /// Restrictions: The SDK only supports the creation of one instance of CopyrightedMusic. Multiple calls to this function return the same object.
    ///
    /// @return copyrighted music instance, multiple calls to this function return the same object.
    virtual IZegoCopyrightedMusic *createCopyrightedMusic() = 0;

    /// Destroys a copyrighted music instance.
    ///
    /// Available since: 2.13.0
    /// Description: Destroys a copyrighted music instance.
    /// When to call: It can be called before the engine by [destroyEngine]
    ///
    /// @param copyrightedMusic The copyrighted music instance object to be destroyed.
    virtual void destroyCopyrightedMusic(IZegoCopyrightedMusic *&copyrightedMusic) = 0;

    /// [Deprecated] Turns on/off verbose debugging and sets up the log language. This function is deprecated in version 2.3.0, please use [enableDebugAssistant] to achieve the original function.
    ///
    /// This feature is disabled by default and the language of debug information is English.
    ///
    /// @deprecated This function is deprecated in version 2.3.0, please use [enableDebugAssistant] to achieve the original function.
    /// @param enable Detailed debugging information switch
    /// @param language Debugging information language. Note that Chinese is deprecated, if you need Chinese info, please refer to the document https://docs.zegocloud.com/en/5548.html
    ZEGO_DEPRECATED
    virtual void setDebugVerbose(bool enable, ZegoLanguage language) = 0;

    /// [Deprecated] Logs in multi room. This method has been deprecated after version 2.9.0 If you want to access the multi-room feature, Please set [setRoomMode] to select multi-room mode before the engine started, and then call [loginRoom] to use multi-room. If you call [loginRoom] function to log in to multiple rooms, please make sure to pass in the same user information.
    ///
    /// This method has been deprecated after version 2.9.0 If you want to access the multi-room feature, Please set [setRoomMode] to select multi-room mode before the engine started, and then call [loginRoom] to use multi-room. If you call [loginRoom] function to log in to multiple rooms, please make sure to pass in the same user information.
    /// You must log in the main room with [loginRoom] before invoke this function to logging in to multi room.
    /// Currently supports logging into 1 main room and 1 multi room at the same time.
    /// When logging out, you must log out of the multi room before logging out of the main room.
    /// User can only publish the stream in the main room, but can play the stream in the main room and multi room at the same time, and can receive the signaling and callback in each room.
    /// The advantage of multi room is that you can login another room without leaving the current room, receive signaling and callback from another room, and play streams from another room.
    /// To prevent the app from being impersonated by a malicious user, you can add authentication before logging in to the room, that is, the [token] parameter in the ZegoRoomConfig object passed in by the [config] parameter.
    /// Different users who log in to the same room can get room related notifications in the same room (eg [onRoomUserUpdate], [onRoomStreamUpdate], etc.), and users in one room cannot receive room signaling notifications in another room.
    /// Messages sent in one room (e.g. [setStreamExtraInfo], [sendBroadcastMessage], [sendBarrageMessage], [sendCustomCommand], etc.) cannot be received callback ((eg [onRoomStreamExtraInfoUpdate], [onIMRecvBroadcastMessage], [onIMRecvBarrageMessage], [onIMRecvCustomCommand], etc) in other rooms. Currently, SDK does not provide the ability to send messages across rooms. Developers can integrate the SDK of third-party IM to achieve.
    /// SDK supports startPlayingStream audio and video streams from different rooms under the same appID, that is, startPlayingStream audio and video streams across rooms. Since ZegoExpressEngine's room related callback notifications are based on the same room, when developers want to startPlayingStream streams across rooms, developers need to maintain related messages and signaling notifications by themselves.
    /// If the network is temporarily interrupted due to network quality reasons, the SDK will automatically reconnect internally. You can get the current connection status of the local room by listening to the [onRoomStateUpdate] callback method, and other users in the same room will receive [onRoomUserUpdate] callback notification.
    /// It is strongly recommended that userID corresponds to the user ID of the business APP, that is, a userID and a real user are fixed and unique, and should not be passed to the SDK in a random userID. Because the unique and fixed userID allows ZEGO technicians to quickly locate online problems.
    ///
    /// @deprecated This method has been deprecated after version 2.9.0 If you want to access the multi-room feature, Please set [setRoomMode] to select multi-room mode before the engine started, and then call [loginRoom] to use multi-room. If you call [loginRoom] function to log in to multiple rooms, please make sure to pass in the same user information.
    /// @param roomID Room ID, a string of up to 128 bytes in length. Only support numbers, English characters and '~', '!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '_', '+', '=', '-', '`', ';', '’', ',', '.', '<', '>', '/', '\'.
    /// @param config Advanced room configuration.
    ZEGO_DEPRECATED
    virtual void loginMultiRoom(const std::string &roomID, ZegoRoomConfig *config = nullptr) = 0;

    /// [Deprecated] Set the selected video layer of playing stream. This function has been deprecated since version 2.3.0, Please use [setPlayStreamVideoType] instead.
    ///
    /// Available: 1.19.0 to 2.3.0, deprecated.
    /// This function has been deprecated since version 2.3.0, Please use [setPlayStreamVideoType] instead.
    /// When the publisher has set the codecID to SVC through [setVideoConfig], the player can dynamically set whether to use the standard layer or the base layer (the resolution of the base layer is one-half of the standard layer)
    /// Under normal circumstances, when the network is weak or the rendered UI form is small, you can choose to use the video that plays the base layer to save bandwidth.
    /// It can be set before and after playing stream.
    /// Note: This function is only available in ZegoExpressVideo SDK!
    ///
    /// @deprecated This function has been deprecated since version 2.3.0, Please use [setPlayStreamVideoType] instead.
    /// @param streamID Stream ID.
    /// @param videoLayer Video layer of playing stream. AUTO by default.
    ZEGO_DEPRECATED
    virtual void setPlayStreamVideoLayer(const std::string &streamID,
                                         ZegoPlayerVideoLayer videoLayer) = 0;

    /// [Deprecated] Enables the callback for receiving audio data. This function has been deprecated since version 2.7.0, please use [startAudioDataObserver] and [stopAudioDataObserver] instead.
    ///
    /// This function has been deprecated since version 2.7.0, please use [startAudioDataObserver] and [stopAudioDataObserver] instead.
    /// The callback to the corresponding setting of [setAudioDataHandler] is triggered when this function is called and at publishing stream state or playing stream state. If you want to enable the [onPlayerAudioData] callback, the sample rate passed in by calling the [enableAudioDataCallback] function does not support 8000Hz, 22050Hz and 24000Hz.
    ///
    /// @deprecated This function has been deprecated since version 2.7.0, please use [startAudioDataObserver] and [stopAudioDataObserver] instead.
    /// @param enable Whether to enable audio data callback
    /// @param callbackBitMask The callback function bitmask marker for receive audio data, refer to enum [ZegoAudioDataCallbackBitMask], when this param converted to binary, 0b01 that means 1 << 0 for triggering [onCapturedAudioData], 0x10 that means 1 << 1 for triggering [onPlaybackAudioData], 0x100 that means 1 << 2 for triggering [onMixedAudioData], 0x1000 that means 1 << 3 for triggering [onPlayerAudioData]. The masks can be combined to allow different callbacks to be triggered simultaneously.
    /// @param param param of audio frame
    ZEGO_DEPRECATED
    virtual void enableAudioDataCallback(bool enable, unsigned int callbackBitMask,
                                         ZegoAudioFrameParam param) = 0;

    /// [Deprecated] Setting up the specific reverberation parameters. This function has been deprecated since version 1.18.0, please use [setReverbAdvancedParam] instead.
    ///
    /// This function has been deprecated since version 1.18.0, please use [setReverbAdvancedParam] instead.
    /// Different values dynamically set during publishing stream will take effect. When all parameters are set to 0, the reverberation is turned off.
    /// This function is an advanced version of [setReverbPreset], you can configure the reverb effect by yourself.
    /// If you need to configure the reverb/echo/voice changer effect, please use [setReverbAdvancedParam], [setReverbEchoParam], [setVoiceChangerParam] together.
    ///
    /// @deprecated This function has been deprecated since version 1.18.0, please use [setReverbAdvancedParam] instead.
    /// @param param Reverb parameter
    ZEGO_DEPRECATED
    virtual void setReverbParam(ZegoReverbParam param) = 0;

#if TARGET_OS_IPHONE || defined(ANDROID)
    /// [Deprecated] Whether to use the built-in speaker to play audio.This function has been deprecated since version 2.3.0 Please use [setAudioRouteToSpeaker] instead.
    ///
    /// This function has been deprecated since version 2.3.0 Please use [setAudioRouteToSpeaker] instead.
    /// When you choose not to use the built-in speaker to play sound, that is, set to false, the SDK will select the currently highest priority audio output device to play the sound according to the system schedule
    ///
    /// @deprecated This function has been deprecated since version 2.3.0 Please use [setAudioRouteToSpeaker] instead.
    /// @param enable Whether to use the built-in speaker to play sound, true: use the built-in speaker to play sound, false: use the highest priority audio output device scheduled by the current system to play sound
    ZEGO_DEPRECATED
    virtual void setBuiltInSpeakerOn(bool enable) = 0;
#endif
};

class IZegoRealTimeSequentialDataManager {
  protected:
    virtual ~IZegoRealTimeSequentialDataManager() {}

  public:
    /// Sets up the real-time sequential data event handler.
    ///
    /// Available since: 2.14.0
    /// Description: Set up real-time sequential data callback to monitor callbacks such as sending data results， receiving data, etc.
    /// When to call:After create the [ZegoRealTimeSequentialDataManager] instance.
    /// Restrictions: None.
    /// Caution: Calling this function will overwrite the callback set by the last call to this function.
    ///
    /// @param handler Event handler for real-time sequential data
    virtual void
    setEventHandler(std::shared_ptr<IZegoRealTimeSequentialDataEventHandler> handler) = 0;

    /// Start broadcasting real-time sequential data stream.
    ///
    /// Available since: 2.14.0
    /// Description: This function allows users to broadcast their local real-time sequential data stream to the ZEGO RTC server, and other users in the same room can subscribe to the real-time sequential data stream for intercommunication through "streamID".
    /// Use cases: Before sending real-time sequential data, you need to call this function to start broadcasting.
    /// When to call: After creating the [ZegoRealTimeSequentialDataManager] instance.
    /// Restrictions: None.
    /// Caution: After calling this function, you will receive the [onPublisherStateUpdate] callback to tell you the broadcast state (publish state) of this stream. After the broadcast is successful, other users in the same room will receive the [onRoomStreamUpdate] callback to tell them this stream has been added to the room.
    ///
    /// @param streamID Stream ID, a string of up to 256 characters, needs to be globally unique within the entire AppID (Note that it cannot be the same as the stream ID passed in [startPublishingStream]). If in the same AppID, different users publish each stream and the stream ID is the same, which will cause the user to publish the stream failure. You cannot include URL keywords, otherwise publishing stream and playing stream will fails. Only support numbers, English characters and '~', '!', '@', '$', '%', '^', '&', '*', '(', ')', '_', '+', '=', '-', '`', ';', '’', ',', '.', '<', '>', '/', '\'.
    virtual void startBroadcasting(const std::string &streamID) = 0;

    /// Stop broadcasting real-time sequential data stream.
    ///
    /// Available since: 2.14.0
    /// Description: This function allows users to stop broadcasting their local real-time sequential data stream.
    /// Use cases: When you no longer need to send real-time sequential data, you need to call this function to stop broadcasting.
    /// When to call: After creating the [ZegoRealTimeSequentialDataManager] instance.
    /// Restrictions: None.
    /// Caution: After calling this function, you will receive the [onPublisherStateUpdate] callback to tell you the broadcast state (publish state) of this stream. After stopping the broadcast, other users in the same room will receive the [onRoomStreamUpdate] callback to tell them this stream has been deleted from the room.
    ///
    /// @param streamID The ID of the stream that needs to stop broadcasting.
    virtual void stopBroadcasting(const std::string &streamID) = 0;

    /// Send real-time sequential data to the broadcasting stream ID.
    ///
    /// Available since: 2.14.0
    /// Description: This function can be used to send real-time sequential data on the stream currently being broadcast.
    /// Use cases: You need to call this function when you need to send real-time sequential data.
    /// When to call: After calling [startBroadcasting].
    /// Restrictions: None.
    /// Caution: None.
    ///
    /// @param data The real-time sequential data to be sent.
    /// @param dataLength Data content length.
    /// @param streamID The stream ID to which the real-time sequential data is sent.
    /// @param callback Send real-time sequential data result callback.
    virtual void sendRealTimeSequentialData(const unsigned char *data, unsigned int dataLength,
                                            const std::string &streamID,
                                            ZegoRealTimeSequentialDataSentCallback callback) = 0;

    /// Start subscribing real-time sequential data stream.
    ///
    /// Available since: 2.14.0
    /// Description: This function allows users to subscribe to the real-time sequential data stream of remote users from the ZEGO RTC server.
    /// Use cases: When you need to receive real-time sequential data sent from other remote users, you need to call this function to start subscribing to the stream broadcasted by other remote users.
    /// When to call: After creating the [ZegoRealTimeSequentialDataManager] instance.
    /// Restrictions: None.
    /// Caution: After calling this function, you will receive the [onPlayerStateUpdate] callback to tell you the subscribe state (play state) of this stream.
    ///
    /// @param streamID Stream ID, a string of up to 256 characters, needs to be globally unique within the entire AppID. If in the same AppID, different users publish each stream and the stream ID is the same, which will cause the user to publish the stream failure. You cannot include URL keywords, otherwise publishing stream and playing stream will fails. Only support numbers, English characters and '~', '!', '@', '$', '%', '^', '&', '*', '(', ')', '_', '+', '=', '-', '`', ';', '’', ',', '.', '<', '>', '/', '\'.
    virtual void startSubscribing(const std::string &streamID) = 0;

    /// Stop subscribing real-time sequential data stream.
    ///
    /// Available since: 2.14.0
    /// Description: This function can be used to stop subscribing to the real-time sequential data stream.
    /// Use cases: When you no longer need to receive real-time sequential data sent by other users, you need to call this function to stop subscribing to the other user's stream.
    /// When to call: After creating the [ZegoRealTimeSequentialDataManager] instance.
    /// Restrictions: None.
    /// Caution: After calling this function, you will receive the [onPlayerStateUpdate] callback to tell you the subscribe state (play state) of this stream.
    ///
    /// @param streamID The ID of the stream that needs to stop subscribing.
    virtual void stopSubscribing(const std::string &streamID) = 0;

    /// Get real-time sequential data manager index.
    ///
    /// @return Index of the real-time sequential data manager.
    virtual int getIndex() = 0;
};

class IZegoAudioEffectPlayer {
  protected:
    virtual ~IZegoAudioEffectPlayer() {}

  public:
    /// Set audio effect player event handler.
    ///
    /// Available since: 1.16.0
    /// Description: Set audio effect player event handler.
    /// When to call: It can be called after [createAudioEffectPlayer].
    /// Restrictions: None.
    /// Related APIs: [createAudioEffectPlayer].
    ///
    /// @param handler event handler for audio effect player.
    virtual void setEventHandler(std::shared_ptr<IZegoAudioEffectPlayerEventHandler> handler) = 0;

    /// Start playing audio effect.
    ///
    /// Available since: 1.16.0
    /// Description: Start playing audio effect. The default is only played once and is not mixed into the publishing stream, if you want to change this please modify [config] param.
    /// Use cases: When you need to play short sound effects, such as applause, cheers, etc., you can use this interface to achieve, and further configure the number of plays through the [config] parameter, and mix the sound effects into the push stream.
    /// When to call: It can be called after [createAudioEffectPlayer].
    /// Restrictions: None.
    ///
    /// @param audioEffectID Description: ID for the audio effect. The SDK uses audioEffectID to control the playback of sound effects. The SDK does not force the user to pass in this parameter as a fixed value. It is best to ensure that each sound effect can have a unique ID. The recommended methods are static self-incrementing ID or the hash of the incoming sound effect file path.
    /// @param path The absolute path of the local resource. <br>Value range: "assets://"、"ipod-library://" and network url are not supported. Set path as nullptr or "" if resource is loaded already using [loadResource].
    /// @param config Audio effect playback configuration. <br>Default value: Set nullptr will only be played once, and will not be mixed into the publishing stream.
    virtual void start(unsigned int audioEffectID, const std::string &path,
                       ZegoAudioEffectPlayConfig *config = nullptr) = 0;

    /// Stop playing audio effect.
    ///
    /// Available since: 1.16.0
    /// Description: Stop playing the specified audio effect [audioEffectID].
    /// When to call: The specified [audioEffectID] is [start].
    /// Restrictions: None.
    ///
    /// @param audioEffectID ID for the audio effect.
    virtual void stop(unsigned int audioEffectID) = 0;

    /// Pause playing audio effect.
    ///
    /// Available since: 1.16.0
    /// Description: Pause playing the specified audio effect [audioEffectID].
    /// When to call: The specified [audioEffectID] is [start].
    /// Restrictions: None.
    ///
    /// @param audioEffectID ID for the audio effect.
    virtual void pause(unsigned int audioEffectID) = 0;

    /// Resume playing audio effect.
    ///
    /// Available since: 1.16.0
    /// Description: Resume playing the specified audio effect [audioEffectID].
    /// When to call: The specified [audioEffectID] is [pause].
    /// Restrictions: None.
    ///
    /// @param audioEffectID ID for the audio effect.
    virtual void resume(unsigned int audioEffectID) = 0;

    /// Stop playing all audio effect.
    ///
    /// Available since: 1.16.0
    /// Description: Stop playing all audio effect.
    /// When to call: Some audio effects are Playing.
    /// Restrictions: None.
    virtual void stopAll() = 0;

    /// Pause playing all audio effect.
    ///
    /// Available since: 1.16.0
    /// Description: Pause playing all audio effect.
    /// When to call: It can be called after [createAudioEffectPlayer].
    /// Restrictions: None.
    virtual void pauseAll() = 0;

    /// Resume playing all audio effect.
    ///
    /// Available since: 1.16.0
    /// Description: Resume playing all audio effect.
    /// When to call: It can be called after [pauseAll].
    /// Restrictions: None.
    virtual void resumeAll() = 0;

    /// Set the specified playback progress.
    ///
    /// Available since: 1.16.0
    /// Description: Set the specified audio effect playback progress. Unit is millisecond.
    /// When to call: The specified [audioEffectID] is[start], and not finished.
    /// Restrictions: None.
    ///
    /// @param audioEffectID ID for the audio effect.
    /// @param millisecond Point in time of specified playback progress.
    /// @param callback The result of seek.
    virtual void seekTo(unsigned int audioEffectID, unsigned long long millisecond,
                        ZegoAudioEffectPlayerSeekToCallback callback) = 0;

    /// Set volume for a single audio effect. Both the local play volume and the publish volume are set.
    ///
    /// Available since: 1.16.0
    /// Description: Set volume for a single audio effect. Both the local play volume and the publish volume are set.
    /// When to call: The specified [audioEffectID] is [start].
    /// Restrictions: None.
    ///
    /// @param audioEffectID ID for the audio effect.
    /// @param volume Volume. <br>Value range: The range is 0 ~ 200. <br>Default value: The default is 100.
    virtual void setVolume(unsigned int audioEffectID, int volume) = 0;

    /// Set volume for all audio effect. Both the local play volume and the publish volume are set.
    ///
    /// Available since: 1.16.0
    /// Description: Set volume for all audio effect. Both the local play volume and the publish volume are set.
    /// When to call: It can be called after [createAudioEffectPlayer].
    /// Restrictions: None.
    ///
    /// @param volume Volume. <br>Value range: The range is 0 ~ 200. <br>Default value: The default is 100.
    virtual void setVolumeAll(int volume) = 0;

    /// Set the playback speed for a given audio effect. Both the local play speed and the publish speed are set. (separate settings are not supported).
    ///
    /// Available since: 2.18.0
    /// Description: Set the playback speed for a given audio effect. Both the local play speed and the publish speed are set. (separate settings are not supported).
    /// When to call: The specified [audioEffectID] is [start].
    /// Restrictions: None.
    ///
    /// @param audioEffectID ID for the audio effect.
    /// @param speed The speed of play. <br>Value range: The range is 0.5 ~ 2.0. <br>Default value: The default is 1.0.
    virtual void setPlaySpeed(unsigned int audioEffectID, float speed) = 0;

    /// Get the total duration of the specified audio effect resource.
    ///
    /// Available since: 1.16.0
    /// Description: Get the total duration of the specified audio effect resource. Unit is millisecond.
    /// When to call: You should invoke this function after the audio effect resource already loaded, otherwise the return value is 0.
    /// Restrictions: It can be called after [createAudioEffectPlayer].
    /// Related APIs: [start], [loadResource].
    ///
    /// @param audioEffectID ID for the audio effect.
    /// @return Unit is millisecond.
    virtual unsigned long long getTotalDuration(unsigned int audioEffectID) = 0;

    /// Get current playback progress.
    ///
    /// Available since: 1.16.0
    /// Description: Get current playback progress of the specified audio effect. Unit is millisecond.
    /// When to call: You should invoke this function after the audio effect resource already loaded, otherwise the return value is 0.
    /// Restrictions: None.
    /// Related APIs: [start], [loadResource].
    ///
    /// @param audioEffectID ID for the audio effect.
    virtual unsigned long long getCurrentProgress(unsigned int audioEffectID) = 0;

    /// Load audio effect resource.
    ///
    /// Available since: 1.16.0
    /// Description: Load audio effect resource.
    /// Use cases: In a scene where the same sound effect is played frequently, the SDK provides the function of preloading the sound effect file into the memory in order to optimize the performance of repeatedly reading and decoding the file.
    /// When to call: It can be called after [createAudioEffectPlayer].
    /// Restrictions: Preloading supports loading up to 15 sound effect files at the same time, and the duration of the sound effect files cannot exceed 30s, otherwise an error will be reported when loading.
    ///
    /// @param audioEffectID ID for the audio effect.
    /// @param path the absolute path of the audio effect resource and cannot be nullptr or "". <br>Value range: "assets://"、"ipod-library://" and network url are not supported.
    /// @param callback load audio effect resource result.
    virtual void loadResource(unsigned int audioEffectID, const std::string &path,
                              ZegoAudioEffectPlayerLoadResourceCallback callback) = 0;

    /// Unload audio effect resource.
    ///
    /// Available since: 1.16.0
    /// Description: Unload the specified audio effect resource.
    /// When to call: After the sound effects are used up, related resources can be released through this function; otherwise, the SDK will release the loaded resources when the AudioEffectPlayer instance is destroyed.
    /// Restrictions: None.
    /// Related APIs: [loadResource].
    ///
    /// @param audioEffectID ID for the audio effect loaded.
    virtual void unloadResource(unsigned int audioEffectID) = 0;

    /// Get audio effect player index.
    ///
    /// Available since: 1.16.0
    /// Description: Get audio effect player index.
    /// When to call: It can be called after [createAudioEffectPlayer].
    /// Restrictions: None.
    ///
    /// @return Audio effect player index.
    virtual int getIndex() = 0;
};

class IZegoRangeAudio {
  protected:
    virtual ~IZegoRangeAudio() {}

  public:
    /// set range audio event handler.
    ///
    /// Available since: 2.11.0
    /// Description: Set the callback function of the range audio module, which can receive the callback notification of the microphone on state [onRangeAudioMicrophoneStateUpdate].
    /// Use case: Used to monitor the connection status of the current microphone.
    /// When to call: After initializing the range audio [createRangeAudio].
    ///
    /// @param handler The object used to receive range audio callbacks.
    virtual void setEventHandler(std::shared_ptr<IZegoRangeAudioEventHandler> handler) = 0;

    /// Set the maximum range of received audio.
    ///
    /// Available since: 2.11.0
    /// Description: Set the audio receiving range, the audio source sound beyond this range will not be received.
    /// Use case: Set the receiver's receiving range in the `World` mode.
    /// Default value: When this function is not called, there is no distance limit, and everyone in the room can be received.
    /// When to call: After initializing the range audio [createRangeAudio].
    /// Restrictions: This range only takes effect for people outside the team.
    ///
    /// @param range the audio range, the value must be greater than or equal to 0.
    virtual void setAudioReceiveRange(float range) = 0;

    /// Update self position and orentation.
    ///
    /// Available since: 2.11.0
    /// Description: Update the user's position and orientation so that the SDK can calculate the distance between the user and the audio source and the stereo effect of the left and right ears.
    /// Use case: When the role operated by the user in the game moves on the world map, the position information and head orientation of the role are updated.
    /// When to call: Called after logging in to the room [loginRoom].
    /// Caution: Before calling [enableSpeaker] to turn on the speaker, if you do not call this interface to set the location information, you will not be able to receive voices from other people except the team.
    ///
    /// @param position The coordinates of the oneself in the world coordinate system. The parameter is a float array of length 3. The three values ​​represent the front, right, and top coordinate values ​​in turn.
    /// @param axisForward The unit vector of the front axis of its own coordinate system. The parameter is a float array with a length of 3. The three values ​​represent the front, right, and top coordinate values ​​in turn.
    /// @param axisRight The unit vector of the right axis of its own coordinate system. The parameter is a float array with a length of 3. The three values ​​represent the front, right, and top coordinate values ​​in turn.
    /// @param axisUp The unit vector of the up axis of its own coordinate system. The parameter is a float array with a length of 3. The three values ​​represent the front, right, and top coordinate values ​​in turn.
    virtual void updateSelfPosition(float position[3], float axisForward[3], float axisRight[3],
                                    float axisUp[3]) = 0;

    /// Add or update audio source position information.
    ///
    /// Available since: 2.11.0
    /// Description: Set the position of the audio source corresponding to the userID on the game map in the room, so that the SDK can calculate the distance and orientation of the listener to the audio source.
    /// Use case: Update the position of the voice user in the game map coordinates.
    /// When to call: Call [loginRoom] to call after logging in to the room, and the recorded audio source information will be cleared after logging out of the room.
    ///
    /// @param userID The user ID of the sender.
    /// @param position The coordinates of the speaker in the world coordinate system. The parameter is a float array of length 3. The three values ​​represent the front, right, and top coordinate values ​​in turn.
    virtual void updateAudioSource(const std::string &userID, float position[3]) = 0;

    /// Turn the 3D spatial sound on or off.
    ///
    /// Available since: 2.11.0
    /// Description: After the 3D sound effect is turned on, the sound effect in the actual space will be simulated according to the position of the speaker equivalent to the listener. The intuitive feeling is that the sound size and the left and right sound difference will also change when the distance and orientation of the sound source change.
    /// Use case: It is a feature of audio recognition in FPS games or social scene games.
    /// Default value: When this function is not called, 3D sound effects are turned off by default.
    /// When to call: After initializing the range audio [createRangeAudio].
    /// Caution: The 3D audio effect will only take effect when [setRangeAudioMode] is called and set to `World` mode.
    /// Related APIs: After enabling the 3D sound effect, you can use [updateAudioSource] or [updateSelfPosition] to change the position and orientation to experience the 3D effect.
    ///
    /// @param enable Whether to enable 3D sound effects.
    virtual void enableSpatializer(bool enable) = 0;

    /// Turn the microphone on or off.
    ///
    /// Available since: 2.11.0
    /// Description: When enable is `true`, turn on the microphone and push audio stream; when it is `false`, turn off the microphone and stop pushing audio stream.
    /// Use case: The user turns on or off the microphone to communicate in the room.
    /// Default value: When this function is not called, the microphone is turned off by default.
    /// When to call: After initializing the range audio [createRangeAudio] and login room [loginRoom].
    /// Caution: Turning on the microphone will automatically use the main channel to push the audio stream.
    /// Related callbacks: Get the microphone switch state change through the callback [onRangeAudioMicrophoneStateUpdate].
    ///
    /// @param enable Whether to turn on the microphone.
    virtual void enableMicrophone(bool enable) = 0;

    /// Turn the speaker on or off.
    ///
    /// Available since: 2.11.0
    /// Description: When enable is `true`, turn on the speaker and play audio stream; when it is `false`, turn off the speaker and stop playing audio stream.
    /// Use case: The user turns on or off the speaker to communicate in the room.
    /// Default value: When this function is not called, the speaker is turned off by default.
    /// When to call: After initializing the range audio [createRangeAudio] and login room [loginRoom].
    /// Caution: Turning on the speaker will automatically pull the audio stream in the room.
    ///
    /// @param enable Whether to turn on the speaker.
    virtual void enableSpeaker(bool enable) = 0;

    /// Set range audio mode.
    ///
    /// Available since: 2.11.0
    /// Description: The audio mode can be set to `World` mode or `Team` mode.
    /// Use case: The user can choose to chat with everyone in the `World` mode (with distance limitation), or to communicate within the team in the `Team` mode (without distance limitation).
    /// Default value: If this function is not called, the `World` mode is used by default.
    /// When to call: After initializing the range audio [createRangeAudio].
    /// Related APIs: In the `World` mode, you can set the sound receiving range [setAudioReceiveRange], in the `Team` mode, you need to set [setTeamID] to join the corresponding team to hear the voice in the team.
    ///
    /// @param mode The range audio mode.
    virtual void setRangeAudioMode(ZegoRangeAudioMode mode) = 0;

    /// Set team ID.
    ///
    /// Available: since 2.11.0
    /// Description: After setting the team ID, you will be able to communicate with other users of the same team, and the sound will not change with the distance.
    /// Use case: Users join the team or exit the team.
    /// Default value: When this function is not called, no team will be added by default.
    /// When to call: After initializing the range audio [createRangeAudio].
    /// Caution: There will be no distance limit for the sounds in the team, and there will be no 3D sound effects.
    /// Restrictions: The team ID will only take effect when [setRangeAudioMode] is called and set to `Team` mode.
    ///
    /// @param teamID Team ID, a string of up to 64 bytes in length. Only support numbers, English characters and '~', '!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '_', '+', '=', '-', '`', ';', '’', ',', '.', '<', '>', '/', '\'.
    virtual void setTeamID(const std::string &teamID) = 0;

    /// Whether can receive the audio data of the specified user.
    ///
    /// Available since: 2.16.0
    /// Description: In the process of real-time audio and video interaction, local users can use this function to control whether to receive audio data from designated remote users when pulling streams as needed. When the developer does not receive the audio receipt, the hardware and network overhead can be reduced.
    /// Use cases: When developers need to quickly close and restore remote audio, they can call this function to enhance the interactive experience.
    /// Default value: The default is `false`, which means to receive audio data from all users.
    /// When to call: After initializing the range audio [createRangeAudio].
    /// Caution: This function is valid only when the [muteAllPlayStreamAudio] function is set to `false`.
    /// Related APIs: You can call the [muteAllPlayStreamAudio] function to control whether to receive all audio data. 1. When the [muteAllPlayStreamAudio(true)] function is called, it takes effect globally, that is, local users will be prohibited from receiving audio data from all remote users. At this time, the [muteUser] function will not take effect regardless of whether the [muteUser] function is called before or after [muteAllPlayStreamAudio]. 2. When the [muteAllPlayStreamAudio(false)] function is called, the local user can receive the audio data of all remote users. At this time, the [muteUser] function can be used to control whether to receive the audio data of the specified user. Calling the [muteUser(userID, true)] function allows the local user to receive audio data other than the `userID`; calling the [muteUser(userID, false)] function allows the local user to receive the audio data of the `userID`.
    ///
    /// @param userID User ID.
    /// @param mute Whether it can receive the audio data of the specified remote user, "true" means prohibition, "false" means receiving, the default value is "false".
    virtual void muteUser(const std::string &userID, bool mute) = 0;
};

class IZegoCopyrightedMusic {
  protected:
    virtual ~IZegoCopyrightedMusic() {}

  public:
    /// set copyrighted music event handler.
    ///
    /// Available since: 2.13.0
    /// Description: Set the callback function of the copyrighted music module, which can receive callback notifications related to song playback status .
    /// When to call: After initializing the copyrighted music [createCopyrightedMusic].
    ///
    /// @param handler The object used to receive copyrighted music callbacks.
    virtual void setEventHandler(std::shared_ptr<IZegoCopyrightedMusicEventHandler> handler) = 0;

    /// Initialize the copyrighted music module.
    ///
    /// Available since: 2.13.0
    /// Description: Initialize the copyrighted music so that you can use the function of the copyrighted music later.
    /// When to call: After initializing the copyrighted music [createCopyrightedMusic].
    /// Restrictions: The real user information must be passed in, otherwise the song resources cannot be obtained for playback.
    ///
    /// @param config the copyrighted music configuration.
    /// @param callback init result
    virtual void initCopyrightedMusic(ZegoCopyrightedMusicConfig config,
                                      ZegoCopyrightedMusicInitCallback callback) = 0;

    /// Get cache size.
    ///
    /// Available since: 2.13.0
    /// Description: When using this module, some cache files may be generated, and the size of the cache file can be obtained through this interface.
    /// Use case: Used to display the cache size of the App.
    /// When to call: After initializing the copyrighted music [createCopyrightedMusic].
    ///
    /// @return cache file size, in byte.
    virtual unsigned long long getCacheSize() = 0;

    /// Clear cache.
    ///
    /// Available since: 2.13.0
    /// Description: When using this module, some cache files may be generated, which can be cleared through this interface.
    /// Use case: Used to clear the cache of the App.
    /// When to call: After initializing the copyrighted music [createCopyrightedMusic].
    virtual void clearCache() = 0;

    /// Send extended feature request.
    ///
    /// Available since: 2.13.0
    /// Description: Initialize the copyrighted music so that you can use the function of the copyrighted music later.
    /// Use case: Used to get a list of songs.
    /// When to call: After initializing the copyrighted music [createCopyrightedMusic].
    ///
    /// @param command request command, see details for specific supported commands.
    /// @param params request parameters, each request command has corresponding request parameters.
    /// @param callback send extended feature request result
    virtual void sendExtendedRequest(const std::string &command, const std::string &params,
                                     ZegoCopyrightedMusicSendExtendedRequestCallback callback) = 0;

    /// Get lyrics in lrc format.
    ///
    /// Available since: 2.13.0
    /// Description: Get lyrics in lrc format, support parsing lyrics line by line.
    /// Use case: Used to display lyrics line by line.
    /// When to call: After initializing the copyrighted music [createCopyrightedMusic].
    ///
    /// @param songID the ID of the song or accompaniment, the song and accompaniment of a song share the same ID.
    /// @param callback get lyrics result
    virtual void getLrcLyric(const std::string &songID,
                             ZegoCopyrightedMusicGetLrcLyricCallback callback) = 0;

    /// Get lyrics in krc format.
    ///
    /// Available since: 2.13.0
    /// Description: Get lyrics in krc format, support parsing lyrics word by word.
    /// Use case: Used to display lyrics word by word.
    /// When to call: After initializing the copyrighted music [createCopyrightedMusic].
    ///
    /// @param krcToken The krcToken obtained by calling requestAccompaniment.
    /// @param callback get lyrics result.
    virtual void getKrcLyricByToken(const std::string &krcToken,
                                    ZegoCopyrightedMusicGetKrcLyricByTokenCallback callback) = 0;

    /// Request a song.
    ///
    /// Available since: 2.13.0
    /// Description: In addition to obtaining the basic information of the song (duration, song name, singer, etc.), and the most important resource id that can be used for local playback, or share_token for sharing to others, there are also some related authentications. information. Support three ways to request a song, pay-per-use, monthly billing by user, and monthly billing by room.
    /// Use case: Get copyrighted songs for local playback and sharing.
    /// When to call: After initializing the copyrighted music [createCopyrightedMusic].
    /// Restrictions: This interface will trigger billing. A song may have three sound qualities: normal, high-definition, and lossless. Each sound quality has a different resource file, and each resource file has a unique resource ID.
    ///
    /// @param config request configuration.
    /// @param callback request a song result
    virtual void requestSong(ZegoCopyrightedMusicRequestConfig config,
                             ZegoCopyrightedMusicRequestSongCallback callback) = 0;

    /// Request accompaniment.
    ///
    /// Available since: 2.13.0
    /// Description: You can get the accompaniment resources of the song corresponding to the songID, including resource_id, krc_token, share_token, etc. Support three ways to request accompaniment, pay-per-use, monthly billing by user, and monthly billing by room.
    /// Use case: Get copyrighted accompaniment for local playback and sharing.
    /// When to call: After initializing the copyrighted music [createCopyrightedMusic].
    /// Restrictions: This interface will trigger billing.
    ///
    /// @param config request configuration.
    /// @param callback request accompaniment result.
    virtual void
    requestAccompaniment(ZegoCopyrightedMusicRequestConfig config,
                         ZegoCopyrightedMusicRequestAccompanimentCallback callback) = 0;

    /// Request accompaniment clip.
    ///
    /// Available since: 2.13.0
    /// Description: You can obtain the climax clip resources of the song corresponding to the songID, including resource_id, krc_token, share_token, etc. Support three ways to request accompaniment clip, pay-per-use, monthly billing by user, and monthly billing by room.
    /// Use case: Get copyrighted accompaniment clip for local playback and sharing.
    /// When to call: After initializing the copyrighted music [createCopyrightedMusic].
    /// Restrictions: This interface will trigger billing.
    ///
    /// @param config request configuration.
    /// @param callback request accompaniment clip result.
    virtual void
    requestAccompanimentClip(ZegoCopyrightedMusicRequestConfig config,
                             ZegoCopyrightedMusicRequestAccompanimentClipCallback callback) = 0;

    /// Get a song or accompaniment.
    ///
    /// Available since: 2.13.0
    /// Description: After the user successfully obtains the song/accompaniment/climax clip resource, he can get the corresponding shareToken, share the shareToken with other users, and other users call this interface to obtain the shared music resources.
    /// Use case: In the online KTV scene, after receiving the song or accompaniment token shared by the lead singer, the chorus obtains the corresponding song or accompaniment through this interface, and then plays it on the local end.
    /// When to call: After initializing the copyrighted music [createCopyrightedMusic].
    ///
    /// @param shareToken access the corresponding authorization token for a song or accompaniment.
    /// @param callback get a song or accompaniment result.
    virtual void getMusicByToken(const std::string &shareToken,
                                 ZegoCopyrightedMusicGetMusicByTokenCallback callback) = 0;

    /// Download song or accompaniment.
    ///
    /// Available since: 2.13.0
    /// Description: Download a song or accompaniment. It can only be played after downloading successfully.
    /// Use case: Get copyrighted accompaniment for local playback and sharing.
    /// When to call: After initializing the copyrighted music [createCopyrightedMusic].
    /// Restrictions: Loading songs or accompaniment resources is affected by the network.
    ///
    /// @param resourceID the resource ID corresponding to the song or accompaniment.
    /// @param callback download song or accompaniment result.
    virtual void download(const std::string &resourceID,
                          ZegoCopyrightedMusicDownloadCallback callback) = 0;

    /// Query the resource's cache is existed or not.
    ///
    /// Available since: 2.13.0
    /// Description: Query the resource is existed or not.
    /// Use case: Can be used to check the resource's cache is existed or not
    /// When to call: After initializing the copyrighted music [createCopyrightedMusic].
    ///
    /// @param songID the ID of the song or accompaniment, the song and accompaniment of a song share the same ID.
    /// @param type the song resource type.
    virtual bool queryCache(const std::string &songID, ZegoCopyrightedMusicType type) = 0;

    /// Get the playing time of a song or accompaniment file.
    ///
    /// Available since: 2.13.0
    /// Description: Get the playing time of a song or accompaniment file.
    /// Use case: Can be used to display the playing time information of the song or accompaniment on the view.
    /// When to call: After initializing the copyrighted music [createCopyrightedMusic].
    ///
    /// @param resourceID the resource ID corresponding to the song or accompaniment.
    virtual unsigned long long getDuration(const std::string &resourceID) = 0;

    /// Start scoring.
    ///
    /// Available since: 2.15.0
    /// Description: Start the scoring function.After starting scoring, the scoring result OnCurrentPitchValueUpdate callback will be received according to the set callback time interval.
    /// Use case: Can be used to display the singing score on the view.
    /// When to call: After obtaining krc verbatim lyrics and playing the accompaniment resources of copyrighted music.
    /// Restrictions: Only support use this api after [startPublishingStream].
    ///
    /// @param resourceID the resource ID corresponding to the song or accompaniment.
    /// @param pitchValueInterval the time interval of real-time pitch line callback, in milliseconds, the default is 50 milliseconds.
    virtual int startScore(const std::string &resourceID, int pitchValueInterval) = 0;

    /// Pause scoring.
    ///
    /// Available since: 2.15.0
    /// Description: Pause ongoing scoring,will stop the [OnCurrentPitchValueUpdate] callback.
    /// Use case: You can call this interface to pause the scoring function while scoring.
    /// When to call: It can be called while grading.
    ///
    /// @param resourceID the resource ID corresponding to the song or accompaniment.
    virtual int pauseScore(const std::string &resourceID) = 0;

    /// Resume scoring.
    ///
    /// Available since: 2.15.0
    /// Description: Resume currently paused scoring.
    /// Use case: When there is currently paused scoring, this interface can be called to resume the scoring function.
    /// When to call: It can be called when there is currently a paused scoring.
    ///
    /// @param resourceID the resource ID corresponding to the song or accompaniment.
    virtual int resumeScore(const std::string &resourceID) = 0;

    /// Stop scoring.
    ///
    /// Available since: 2.15.0
    /// Description: End the current rating.The [OnCurrentPitchValueUpdate] callback will be stopped, but the average or total score can still be obtained normally.
    /// Use case: You can call this interface to end the scoring while scoring.
    /// When to call: It can be called while grading.
    ///
    /// @param resourceID the resource ID corresponding to the song or accompaniment.
    virtual int stopScore(const std::string &resourceID) = 0;

    /// Reset scoring.
    ///
    /// Available since: 2.15.0
    /// Description: Reset the scores that have already been performed,The [OnCurrentPitchValueUpdate] callback will be stopped and the average or total score will be 0.
    /// Use case: Often used in scenes where the same song is re-sung.
    /// When to call: It can be called after scoring has been performed.
    ///
    /// @param resourceID the resource ID corresponding to the song or accompaniment.
    virtual int resetScore(const std::string &resourceID) = 0;

    /// Get the score of the previous sentence.
    ///
    /// Available since: 2.15.0
    /// Description: Get the score of the previous sentence.
    /// Use case: Can be used to display the score of each sentence on the view.
    /// When to call: After obtaining krc verbatim lyrics and playing the accompaniment resources of copyrighted music.The user gets it once after singing each sentence.
    ///
    /// @param resourceID the resource ID corresponding to the song or accompaniment.
    virtual int getPreviousScore(const std::string &resourceID) = 0;

    /// Get average score.
    ///
    /// Available since: 2.15.0
    /// Description: Get the average score.
    /// Use case: Can be used to display the average score on the view.
    /// When to call: After obtaining krc verbatim lyrics and playing the accompaniment resources of copyrighted music.
    ///
    /// @param resourceID the resource ID corresponding to the song or accompaniment.
    virtual int getAverageScore(const std::string &resourceID) = 0;

    /// Get total score .
    ///
    /// Available since: 2.15.0
    /// Description: Get the total score.
    /// Use case: Can be used to display the total score on the view.
    /// When to call: After obtaining krc verbatim lyrics and playing the accompaniment resources of copyrighted music.
    ///
    /// @param resourceID the resource ID corresponding to the song or accompaniment.
    virtual int getTotalScore(const std::string &resourceID) = 0;

    /// Get standard pitch data.
    ///
    /// Available since: 2.15.0
    /// Description: Get standard pitch data.
    /// Use case: Can be used to display standard pitch lines on the view.
    /// Restrictions: Only accompaniment or climactic clip assets have pitch lines.
    ///
    /// @param resourceID the resource ID corresponding to the song or accompaniment.
    /// @param callback get standard pitch data result.
    virtual void getStandardPitch(const std::string &resourceID,
                                  ZegoCopyrightedMusicGetStandardPitchCallback callback) = 0;

    /// Get total score .
    ///
    /// Available since: 2.15.0
    /// Description: Get real-time pitch data.
    /// Use case: Can be used to display real-time pitch lines on the view.
    /// When to call: It can be called after playing the copyright accompaniment and starting to score.
    ///
    /// @param resourceID the resource ID corresponding to the song or accompaniment.
    virtual int getCurrentPitch(const std::string &resourceID) = 0;
};
/// Zego MediaPlayer.
///
/// Yon can use ZegoMediaPlayer to play media resource files on the local or remote server, and can mix the sound of the media resource files that are played into the publish stream to achieve the effect of background music.
class IZegoMediaPlayer {
  protected:
    virtual ~IZegoMediaPlayer() {}

  public:
    /// Set event callback handler for media player.
    ///
    /// Developers can change the player UI widget according to the related event callback of the media player
    ///
    /// @param handler Media player event callback object
    virtual void setEventHandler(std::shared_ptr<IZegoMediaPlayerEventHandler> handler) = 0;

    /// Set video callback handler.
    ///
    /// Developers can set this callback to throw the video data of the media resource file played by the media player
    /// Note: This function is only available in ZegoExpressVideo SDK!
    ///
    /// @param handler Video event callback object for media player
    /// @param format Video frame format for video data
    virtual void setVideoHandler(std::shared_ptr<IZegoMediaPlayerVideoHandler> handler,
                                 ZegoVideoFrameFormat format) = 0;

    /// Set audio callback handler.
    ///
    /// You can set this callback to throw the audio data of the media resource file played by the media player
    ///
    /// @param handler Audio event callback object for media player
    virtual void setAudioHandler(std::shared_ptr<IZegoMediaPlayerAudioHandler> handler) = 0;

    /// Load media resource.
    ///
    /// Available: since 1.3.4
    /// Description: Load media resources.
    /// Use case: Developers can load the absolute path to the local resource or the URL of the network resource incoming.
    /// When to call: It can be called after the engine by [createEngine] has been initialized and the media player has been created by [createMediaPlayer].
    /// Related APIs: Resources can be loaded through the [loadResourceWithPosition] or [loadResourceFromMediaData] function.
    ///
    /// @param path The absolute resource path or the URL of the network resource and cannot be nullptr or "".
    /// @param callback Notification of resource loading results
    virtual void loadResource(const std::string &path,
                              ZegoMediaPlayerLoadResourceCallback callback) = 0;

    /// Load media resource.
    ///
    /// Available: since 2.14.0
    /// Description: Load media resources, and specify the progress, in milliseconds, at which playback begins.
    /// Use case: Developers can load the absolute path to the local resource or the URL of the network resource incoming.
    /// When to call: It can be called after the engine by [createEngine] has been initialized and the media player has been created by [createMediaPlayer].
    /// Related APIs: Resources can be loaded through the [loadResource] or [loadResourceFromMediaData] function.
    /// Caution: When [startPosition] exceeds the total playing time, it will start playing from the beginning.
    ///
    /// @param path The absolute resource path or the URL of the network resource and cannot be nullptr or "".
    /// @param startPosition The progress at which the playback started.
    /// @param callback Notification of resource loading results
    virtual void loadResourceWithPosition(const std::string &path, unsigned long long startPosition,
                                          ZegoMediaPlayerLoadResourceCallback callback) = 0;

    /// Load media resource.
    ///
    /// Available: since 2.10.0
    /// Description: Load binary audio data.
    /// Use case: Developers do not want to cache the audio data locally, and directly transfer the audio binary data to the media player, directly load and play the audio.
    /// When to call: It can be called after the engine by [createEngine] has been initialized and the media player has been created by [createMediaPlayer].
    /// Related APIs: Resources can be loaded through the [loadResource] or [loadResourceWithPosition] function.
    /// Caution: When [startPosition] exceeds the total playing time, it will start playing from the beginning.
    ///
    /// @param media_data Binary audio data.
    /// @param media_data_length The length of the binary audio data.
    /// @param start_position Position of starting playback, in milliseconds.
    /// @param callback Notification of resource loading results.
    virtual void loadResourceFromMediaData(unsigned char *media_data, int media_data_length,
                                           unsigned long long start_position,
                                           ZegoMediaPlayerLoadResourceCallback callback) = 0;

    /// Load copyrighted music resource.
    ///
    /// Available: since 2.14.0
    /// Description: Load media resources, and specify the progress, in milliseconds, at which playback begins.
    /// Use case: Developers can load the resource ID of copyrighted music.
    /// When to call: It can be called after the engine by [createEngine] has been initialized and the media player has been created by [createMediaPlayer].
    /// Caution: When [startPosition] exceeds the total playing time, it will start playing from the beginning.
    ///
    /// @param resourceID The resource ID obtained from the copyrighted music module.
    /// @param startPosition The progress at which the playback started.
    /// @param callback Notification of resource loading results
    virtual void
    loadCopyrightedMusicResourceWithPosition(const std::string &resourceID,
                                             unsigned long long startPosition,
                                             ZegoMediaPlayerLoadResourceCallback callback) = 0;

    /// Start playing.
    ///
    /// You need to load resources before playing
    virtual void start() = 0;

    /// Stop playing.
    virtual void stop() = 0;

    /// Pause playing.
    virtual void pause() = 0;

    /// resume playing.
    virtual void resume() = 0;

    /// Set the specified playback progress.
    ///
    /// Unit is millisecond
    ///
    /// @param millisecond Point in time of specified playback progress
    /// @param callback the result notification of set the specified playback progress
    virtual void seekTo(unsigned long long millisecond, ZegoMediaPlayerSeekToCallback callback) = 0;

    /// Whether to repeat playback.
    ///
    /// @param enable repeat playback flag. The default is false.
    virtual void enableRepeat(bool enable) = 0;

    /// Set the count of play loops.
    ///
    /// Available: since 2.10.0
    /// Description: Set the count of play loops.
    /// Use cases: Users can call this function when they need to use the media player to loop playback resources.
    /// When to call /Trigger: It can be called after the engine by [createEngine] has been initialized and the media player has been created by [createMediaPlayer].
    /// Restrictions: None.
    /// Caution: Please note that after using this interface, the [enableRepeat] interface will become invalid.
    ///
    /// @param count the count of play loops
    virtual void setPlayLoopCount(int count) = 0;

    /// Set the speed of play.
    ///
    /// Available since: 2.12.0
    /// Description: Set the playback speed of the player.
    /// When to call: You should load resource before invoking this function.
    /// Restrictions: None.
    /// Related APIs: Resources can be loaded through the [loadResource] function.
    ///
    /// @param speed The speed of play. The range is 0.5 ~ 2.0. The default is 1.0.
    virtual void setPlaySpeed(float speed) = 0;

    /// Whether to mix the player's sound into the main stream channel being published.
    ///
    /// @param enable Aux audio flag. The default is false.
    virtual void enableAux(bool enable) = 0;

    /// Whether to play locally silently.
    ///
    /// If [enableAux] switch is turned on, there is still sound in the publishing stream. The default is false.
    ///
    /// @param mute Mute local audio flag, The default is false.
    virtual void muteLocal(bool mute) = 0;

    /// Set the view of the player playing video.
    /// Note: This function is only available in ZegoExpressVideo SDK!
    ///
    /// @param canvas Video rendered canvas object
    virtual void setPlayerCanvas(ZegoCanvas *canvas) = 0;

    /// Set mediaplayer volume. Both the local play volume and the publish volume are set.
    ///
    /// @param volume The range is 0 ~ 200. The default is 60.
    virtual void setVolume(int volume) = 0;

    /// Set mediaplayer local play volume.
    ///
    /// @param volume The range is 0 ~ 200. The default is 60.
    virtual void setPlayVolume(int volume) = 0;

    /// Set mediaplayer publish volume.
    ///
    /// @param volume The range is 0 ~ 200. The default is 60.
    virtual void setPublishVolume(int volume) = 0;

    /// Set playback progress callback interval.
    ///
    /// This function can control the callback frequency of [onMediaPlayerPlayingProgress]. When the callback interval is set to 0, the callback is stopped. The default callback interval is 1s
    /// This callback are not returned exactly at the set callback interval, but rather at the frequency at which the audio or video frames are processed to determine whether the callback is needed to call
    ///
    /// @param millisecond Interval of playback progress callback in milliseconds
    virtual void setProgressInterval(unsigned long long millisecond) = 0;

    /// Gets the current local playback volume of the mediaplayer, the range is 0 ~ 200, with the default value of 60.
    virtual int getPlayVolume() = 0;

    /// Gets the current publish volume of the mediaplayer, the range is 0 ~ 200, with the default value of 60.
    virtual int getPublishVolume() = 0;

    /// Get the total progress of your media resources.
    ///
    /// You should load resource before invoking this function, otherwise the return value is 0
    ///
    /// @return Unit is millisecond
    virtual unsigned long long getTotalDuration() = 0;

    /// Get current playing progress.
    ///
    /// You should load resource before invoking this function, otherwise the return value is 0
    virtual unsigned long long getCurrentProgress() = 0;

    /// Get the number of audio tracks of the playback file.
    virtual unsigned int getAudioTrackCount() = 0;

    /// Set the audio track of the playback file.
    ///
    /// @param index Audio track index, the number of audio tracks can be obtained through the [getAudioTrackCount] function.
    virtual void setAudioTrackIndex(unsigned int index) = 0;

    /// Setting up the specific voice changer parameters.
    ///
    /// @param audioChannel The audio channel to be voice changed
    /// @param param Voice changer parameters
    virtual void setVoiceChangerParam(ZegoMediaPlayerAudioChannel audioChannel,
                                      ZegoVoiceChangerParam param) = 0;

    /// Get the current playback status.
    virtual ZegoMediaPlayerState getCurrentState() = 0;

    /// Get media player index.
    virtual int getIndex() = 0;

    /// Take a screenshot of the current playing screen of the media player.
    ///
    /// Only in the case of calling [setPlayerCanvas] to set the display controls and the playback state, can the screenshot be taken normally
    /// Note: This function is only available in ZegoExpressVideo SDK!
    ///
    /// @param callback The callback of the screenshot of the media player playing screen
    virtual void takeSnapshot(ZegoMediaPlayerTakeSnapshotCallback callback) = 0;

    /// Open precise seek and set relevant attributes.
    ///
    /// Call the setting before loading the resource. After setting, it will be valid throughout the life cycle of the media player. For multiple calls to ‘enableAccurateSeek’, the configuration is an overwrite relationship, and each call to ‘enableAccurateSeek’ only takes effect on the resources loaded later.
    ///
    /// @param enable Whether to enable accurate seek
    /// @param config The property setting of precise seek is valid only when enable is true.
    virtual void enableAccurateSeek(bool enable, ZegoAccurateSeekConfig *config) = 0;

    /// Set the maximum cache duration and cache data size of web materials.
    ///
    /// The setting must be called before loading the resource, and it will take effect during the entire life cycle of the media player.
    /// Time and size are not allowed to be 0 at the same time. The SDK internal default time is 5000, and the size is 15*1024*1024 byte.When one of time and size reaches the set value first, the cache will stop.
    ///
    /// @param time The maximum length of the cache time, in ms, the SDK internal default is 5000; the effective value is greater than or equal to 2000; if you fill in 0, it means no limit.
    /// @param size The maximum size of the cache, the unit is byte, the internal default size of the SDK is 15*1024*1024 byte; the effective value is greater than or equal to 5000000, if you fill in 0, it means no limit.
    virtual void setNetWorkResourceMaxCache(unsigned int time, unsigned int size) = 0;

    /// Get the playable duration and size of the cached data of the current network material cache queue
    ///
    /// @return Returns the current cached information, including the length of time the data can be played and the size of the cached data.
    virtual ZegoNetWorkResourceCache *getNetWorkResourceCache() = 0;

    /// Use this interface to set the cache threshold that the media player needs to resume playback. The SDK default value is 5000ms，The valid value is greater than or equal to 1000ms
    ///
    /// @param threshold Threshold that needs to be reached to resume playback, unit ms.
    virtual void setNetWorkBufferThreshold(unsigned int threshold) = 0;

    /// Whether to enable sound level monitoring.
    ///
    /// Available since: 2.15.0
    /// Description: Whether to enable sound level monitoring.
    /// When to call: It can be called after the engine by [createEngine] has been initialized and the media player has been created by [createMediaPlayer].
    /// Restrictions: None.
    /// Related callbacks: After it is turned on, user can use the [onMediaPlayerSoundLevelUpdate] callback to monitor sound level updates.
    ///
    /// @param enable Whether to enable monitoring, true is enabled, false is disabled.
    /// @param millisecond Monitoring time period of the sound level, in milliseconds, has a value range of [100, 3000].
    virtual void enableSoundLevelMonitor(bool enable, unsigned int millisecond) = 0;

    /// Whether to enable frequency spectrum monitoring.
    ///
    /// Available since: 2.15.0
    /// Description: Whether to enable frequency spectrum monitoring.
    /// When to call: It can be called after the engine by [createEngine] has been initialized and the media player has been created by [createMediaPlayer].
    /// Restrictions: None.
    /// Related APIs: After it is turned on, user can use the [onMediaPlayerFrequencySpectrumUpdate] callback to monitor frequency spectrum updates.
    ///
    /// @param enable Whether to enable monitoring, true is enabled, false is disabled.
    /// @param millisecond Monitoring time period of the frequency spectrum, in milliseconds, has a value range of [100, 3000].
    virtual void enableFrequencySpectrumMonitor(bool enable, unsigned int millisecond) = 0;

    /// Set the playback channel.
    ///
    /// Available since: 2.20.0
    /// Description: Set the playback channel.
    /// When to call: It can be called after the engine by [createEngine] has been initialized and the media player has been created by [createMediaPlayer].
    /// Restrictions: None.
    ///
    /// @param audioChannel Playback channel, the default is ZegoMediaPlayerAudioChannelAll.
    virtual void setActiveAudioChannel(ZegoMediaPlayerAudioChannel audioChannel) = 0;

    /// Clears the last frame of the playback control that remains on the control after playback ends.
    ///
    /// Available since: 2.20.0
    /// Description: Clears the last frame of the playback control that remains on the control after playback ends.
    /// When to call: It can be called after the engine by [createEngine] has been initialized and the media player has been created by [createMediaPlayer].
    /// Restrictions: The interface call takes effect only when the media player ends playing.
    virtual void clearView() = 0;
};

/// Zego Media Data Publisher.
///
/// Available since: 2.17.0
/// Description: Yon can use ZegoMediaDataPublisher to publish media resource files on the local end, to achieve server-side publishing stream scenarios, such as AI classrooms.
/// Use cases: Often used in server-side publishing stream scenarios, such as AI classrooms.
class IZegoMediaDataPublisher {
  protected:
    virtual ~IZegoMediaDataPublisher() {}

  public:
    /// Add media file to the publish queue. Currently, only mp4 file are supported, and special conversion is required.
    ///
    /// Available since: 2.17.0
    /// Description: Add media file to the publish queue. Currently, only mp4 file are supported, and special conversion is required.
    /// Use cases: Often used in server-side publishing stream scenarios, such as AI classrooms.
    /// When to call: After calling the [createMediaDataPublisher] function to create a media data publisher.
    /// Caution: The mp4 file format must meet the following points：The video must be encoded as H.264 and cannot contain B frames, only I and P frames. The I frame interval is 2s, that is, a single GOP value is 2s; The frame rate, bit rate, and resolution of the video are consistent with the frame rate, bit rate, and resolution set by [setVideoConfig] before publishing stream; Audio encoding must be MPEG-4 AAC.
    virtual void addMediaFilePath(const std::string &path, bool is_clear) = 0;

    /// Add media file to the publish queue. Currently, only mp4 file are supported, and special conversion is required.
    ///
    /// Available since: 2.17.0
    /// Description: When you need to re-publish stream and do not need to continue publishing from the previous publish queue, you can call this function to reset the MediaDataPublisher state.
    /// Use cases: Often used in server-side publishing stream scenarios, such as AI classrooms.
    /// When to call: Before [startPublishingStream].
    /// Caution: When the developer calls [logoutRoom], the state is automatically reset.
    virtual void reset() = 0;

    /// Set to postpone the video playback time, mainly used to correct the fixed audio and picture asynchronous phenomenon that occurs during the publishing stream.
    ///
    /// Available since: 2.17.0
    /// Description: When this value is set, when publishing video file stream, the SDK will permanently delay the video to the set time value before sending.
    /// Use cases: Often used in server-side publishing stream scenarios, such as AI classrooms.
    /// When to call: After calling the [createMediaDataPublisher] function to create a media data publisher.
    ///
    /// @param delayTime Video playback time.Required: Yes.Value range: [0, 100] ms.
    virtual void setVideoSendDelayTime(int delayTime) = 0;

    /// Specify the starting point of the current video file publishing.
    ///
    /// Available since: 2.17.0
    /// Description: Specify the starting point of the current video file publishing.
    /// Use cases: Often used in server-side publishing stream scenarios, such as AI classrooms.
    /// When to call: Called at any point between [OnMediaDataPublisherFileOpen] and [OnMediaDataPublisherFileClose]. For example: this function can be called directly in the [OnMediaDataPublisherFileOpen] callback.
    ///
    /// @param millisecond The timestamp of the start of streaming (relative to the timestamp of the file currently being published, the starting value is 0). the unit is milliseconds
    virtual void seekTo(unsigned long long millisecond) = 0;

    /// Get the total duration of the current file.
    ///
    /// Available since: 2.17.0
    /// Description: Get the total duration of the current file, in milliseconds.
    /// Use cases: Often used in server-side publishing stream scenarios, such as AI classrooms.
    /// When to call: After [onMediaDataPublisherFileDataBegin] callback.
    virtual unsigned long long getTotalDuration() = 0;

    /// Get the progress of the current file.
    ///
    /// Available since: 2.17.0
    /// Description: Get the progress of the current file, in milliseconds.
    /// Use cases: Often used in server-side publishing stream scenarios, such as AI classrooms.
    /// When to call: After [onMediaDataPublisherFileDataBegin] callback.
    virtual unsigned long long getCurrentDuration() = 0;

    /// Set event callback handler for media data publisher.
    ///
    /// Available since: 2.17.0
    /// Description: Set event callback handler for media data publisher.
    /// Use cases: Often used in server-side publishing stream scenarios, such as AI classrooms.
    /// When to call: After calling the [createMediaDataPublisher] function to create a media data publisher.
    virtual void setMediaDataPublisherEventHandler(
        std::shared_ptr<IZegoMediaDataPublisherEventHandler> handler) = 0;
};

} // namespace EXPRESS
} // namespace ZEGO

#endif // __ZEGOEXPRESSINTERFACE_H__

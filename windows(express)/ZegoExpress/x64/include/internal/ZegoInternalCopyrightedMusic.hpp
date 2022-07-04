#pragma once

#include "../ZegoExpressDefines.h"
#include "../ZegoExpressEventHandler.h"
#include "../ZegoExpressInterface.h"

#include "ZegoInternalBase.h"
#include "ZegoInternalBridge.h"

#define COPYRIGHTEDMUSIC_COPY_CHAR_TO_STD(param) std::string std##param = param;
namespace ZEGO {
namespace EXPRESS {

class ZegoExpressCopyrightedMusicImp : public IZegoCopyrightedMusic {
  public:
    ZegoExpressCopyrightedMusicImp(int index) {}

    void setEventHandler(std::shared_ptr<IZegoCopyrightedMusicEventHandler> handler) override {
        std::lock_guard<std::mutex> loc(copyrightedMusicEventMutex);
        eventHandler = handler;
    }

    void initCopyrightedMusic(ZegoCopyrightedMusicConfig config,
                              ZegoCopyrightedMusicInitCallback callback) override {
        zego_copyrighted_music_config _config;

        memset(&_config.user.user_id, 0, sizeof(_config.user.user_id));
        memset(&_config.user.user_name, 0, sizeof(_config.user.user_name));
        ZegoStrncpy(_config.user.user_id, config.user.userID.c_str(), ZEGO_EXPRESS_MAX_USERID_LEN);
        ZegoStrncpy(_config.user.user_name, config.user.userName.c_str(),
                    ZEGO_EXPRESS_MAX_USERNAME_LEN);

        int seq = oInternalOriginBridge->copyrightedMusicInitCopyrightedMusic(_config);
        if (callback != nullptr) {
            std::lock_guard<std::mutex> lock(copyrightedMusicEventMutex);
            initCallbacks.insert({seq, callback});
        }
    }

    unsigned long long getCacheSize() override {
        return oInternalOriginBridge->copyrightedMusicGetCacheSize();
    }

    void clearCache() override { oInternalOriginBridge->copyrightedMusicClearCache(); }

    void sendExtendedRequest(const std::string &command, const std::string &params,
                             ZegoCopyrightedMusicSendExtendedRequestCallback callback) override {
        const char *_command = command.empty() ? nullptr : command.c_str();
        const char *_params = params.empty() ? nullptr : params.c_str();

        int seq = oInternalOriginBridge->copyrightedMusicSendExtendedRequest(_command, _params);
        if (callback != nullptr) {
            std::lock_guard<std::mutex> lock(copyrightedMusicEventMutex);
            sendExtendedRequestCallbacks.insert({seq, callback});
        }
    }

    void getLrcLyric(const std::string &songID,
                     ZegoCopyrightedMusicGetLrcLyricCallback callback) override {
        const char *_songID = songID.empty() ? nullptr : songID.c_str();

        int seq = oInternalOriginBridge->copyrightedMusicGetLrcLyric(_songID);
        if (callback) {
            std::lock_guard<std::mutex> lock(copyrightedMusicEventMutex);
            getLrcLyricCallbacks.insert({seq, callback});
        }
    }

    void getKrcLyricByToken(const std::string &krcToken,
                            ZegoCopyrightedMusicGetKrcLyricByTokenCallback callback) override {
        const char *_krcToken = krcToken.empty() ? nullptr : krcToken.c_str();

        int seq = oInternalOriginBridge->copyrightedMusicGetKrcLyricByToken(_krcToken);
        if (callback) {
            std::lock_guard<std::mutex> lock(copyrightedMusicEventMutex);
            getKrcLyricByTokenCallbacks.insert({seq, callback});
        }
    }

    void requestSong(ZegoCopyrightedMusicRequestConfig config,
                     ZegoCopyrightedMusicRequestSongCallback callback) override {
        zego_copyrighted_music_request_config _config;
        memset(&_config.song_id, 0, sizeof(_config.song_id));
        ZegoStrncpy(_config.song_id, config.songID.c_str(), ZEGO_EXPRESS_MAX_COMMON_LEN);
        _config.mode = (zego_copyrighted_music_billing_mode)config.mode;

        int seq = oInternalOriginBridge->copyrightedMusicRequestSong(_config);
        if (callback) {
            std::lock_guard<std::mutex> lock(copyrightedMusicEventMutex);
            cmOrderSongCallbacks.insert({seq, callback});
        }
    }

    void requestAccompaniment(ZegoCopyrightedMusicRequestConfig config,
                              ZegoCopyrightedMusicRequestAccompanimentCallback callback) override {
        zego_copyrighted_music_request_config _config;
        memset(&_config.song_id, 0, sizeof(_config.song_id));
        ZegoStrncpy(_config.song_id, config.songID.c_str(), ZEGO_EXPRESS_MAX_COMMON_LEN);
        _config.mode = (zego_copyrighted_music_billing_mode)config.mode;

        int seq = oInternalOriginBridge->copyrightedMusiRequestAccompaniment(_config);
        if (callback) {
            std::lock_guard<std::mutex> lock(copyrightedMusicEventMutex);
            orderAccompanimentCallbacks.insert({seq, callback});
        }
    }

    void requestAccompanimentClip(
        ZegoCopyrightedMusicRequestConfig config,
        ZegoCopyrightedMusicRequestAccompanimentClipCallback callback) override {
        zego_copyrighted_music_request_config _config;
        memset(&_config.song_id, 0, sizeof(_config.song_id));
        ZegoStrncpy(_config.song_id, config.songID.c_str(), ZEGO_EXPRESS_MAX_COMMON_LEN);
        _config.mode = (zego_copyrighted_music_billing_mode)config.mode;

        int seq = oInternalOriginBridge->copyrightedMusiRequestAccompanimentClip(_config);
        if (callback) {
            std::lock_guard<std::mutex> lock(copyrightedMusicEventMutex);
            orderAccompanimentClipCallbacks.insert({seq, callback});
        }
    }

    void getMusicByToken(const std::string &songToken,
                         ZegoCopyrightedMusicGetMusicByTokenCallback callback) override {
        const char *_songToken = songToken.empty() ? nullptr : songToken.c_str();

        int seq = oInternalOriginBridge->copyrightedMusicGetMusicByToken(_songToken);
        if (callback) {
            std::lock_guard<std::mutex> lock(copyrightedMusicEventMutex);
            getMusicByTokenCallbacks.insert({seq, callback});
        }
    }

    void download(const std::string &resourceID,
                  ZegoCopyrightedMusicDownloadCallback callback) override {
        const char *_resourceID = resourceID.empty() ? nullptr : resourceID.c_str();

        int seq = oInternalOriginBridge->copyrightedMusicDownload(_resourceID);
        if (callback) {
            std::lock_guard<std::mutex> lock(copyrightedMusicEventMutex);
            loadCallbacks.insert({seq, callback});
        }
    }

    bool queryCache(const std::string &songID, ZegoCopyrightedMusicType type) override {
        const char *_songID = songID.empty() ? nullptr : songID.c_str();

        bool result = oInternalOriginBridge->copyrightedMusicQueryCache(
            _songID, (zego_copyrighted_music_type)type);
        return result;
    }

    unsigned long long getDuration(const std::string &resourceID) override {
        const char *_resourceID = resourceID.empty() ? nullptr : resourceID.c_str();

        unsigned long long totalDuration =
            oInternalOriginBridge->copyrightedMusicGetDuration(_resourceID);
        return totalDuration;
    }

    int startScore(const std::string &resourceID, int pitchValueInterval) override {
        const char *_resourceID = resourceID.empty() ? nullptr : resourceID.c_str();

        int ret =
            oInternalOriginBridge->copyrightedMusicStartScore(_resourceID, pitchValueInterval);
        return ret;
    }

    int pauseScore(const std::string &resourceID) override {
        const char *_resourceID = resourceID.empty() ? nullptr : resourceID.c_str();

        int ret = oInternalOriginBridge->copyrightedMusicPauseScore(_resourceID);
        return ret;
    }

    int resumeScore(const std::string &resourceID) override {
        const char *_resourceID = resourceID.empty() ? nullptr : resourceID.c_str();

        int ret = oInternalOriginBridge->copyrightedMusicResumeScore(_resourceID);
        return ret;
    }

    int stopScore(const std::string &resourceID) override {
        const char *_resourceID = resourceID.empty() ? nullptr : resourceID.c_str();

        int ret = oInternalOriginBridge->copyrightedMusicStopScore(_resourceID);
        return ret;
    }

    int resetScore(const std::string &resourceID) override {
        const char *_resourceID = resourceID.empty() ? nullptr : resourceID.c_str();

        int ret = oInternalOriginBridge->copyrightedMusicResetScore(_resourceID);
        return ret;
    }

    int getPreviousScore(const std::string &resourceID) override {
        const char *_resourceID = resourceID.empty() ? nullptr : resourceID.c_str();

        int ret = oInternalOriginBridge->copyrightedMusicGetPreviousScore(_resourceID);
        return ret;
    }

    int getAverageScore(const std::string &resourceID) override {
        const char *_resourceID = resourceID.empty() ? nullptr : resourceID.c_str();

        int ret = oInternalOriginBridge->copyrightedMusicGetAverageScore(_resourceID);
        return ret;
    }

    int getTotalScore(const std::string &resourceID) override {
        const char *_resourceID = resourceID.empty() ? nullptr : resourceID.c_str();

        int ret = oInternalOriginBridge->copyrightedMusicGetTotalScore(_resourceID);
        return ret;
    }

    int getCurrentPitch(const std::string &resourceID) override {
        const char *_resourceID = resourceID.empty() ? nullptr : resourceID.c_str();

        int ret = oInternalOriginBridge->copyrightedMusicGetCurrentPitch(_resourceID);
        return ret;
    }

    void getStandardPitch(const std::string &resourceID,
                          ZegoCopyrightedMusicGetStandardPitchCallback callback) override {
        const char *_resourceID = resourceID.empty() ? nullptr : resourceID.c_str();

        int seq = oInternalOriginBridge->copyrightedMusicGetStandardPitch(_resourceID);
        if (callback) {
            std::lock_guard<std::mutex> lock(copyrightedMusicEventMutex);
            getStandardPitchCallbacks.insert({seq, callback});
        }
    }

    void zego_on_copyrighted_music_download_progress_update(const char *resource_id,
                                                            float progress_rate) {
        std::lock_guard<std::mutex> lock(copyrightedMusicEventMutex);
        if (eventHandler) {
            auto weakEventHandler = std::weak_ptr<IZegoCopyrightedMusicEventHandler>(eventHandler);
            COPYRIGHTEDMUSIC_COPY_CHAR_TO_STD(resource_id);
            ZEGO_SWITCH_THREAD_PRE
            auto handlerInMain = weakEventHandler.lock();
            if (handlerInMain) {
                handlerInMain->onDownloadProgressUpdate(this, stdresource_id, progress_rate);
            }
            ZEGO_SWITCH_THREAD_ING
        }
    }

    void zego_on_copyrighted_music_current_pitch_value_update(const char *resource_id,
                                                              int current_duration,
                                                              int pitch_value) {
        std::lock_guard<std::mutex> lock(copyrightedMusicEventMutex);
        if (eventHandler) {
            auto weakEventHandler = std::weak_ptr<IZegoCopyrightedMusicEventHandler>(eventHandler);
            COPYRIGHTEDMUSIC_COPY_CHAR_TO_STD(resource_id);
            ZEGO_SWITCH_THREAD_PRE
            auto handlerInMain = weakEventHandler.lock();
            if (handlerInMain) {
                handlerInMain->onCurrentPitchValueUpdate(this, stdresource_id, current_duration,
                                                         pitch_value);
            }
            ZEGO_SWITCH_THREAD_ING
        }
    }

    // seq
    void zego_on_copyrighted_music_init(zego_seq seq, zego_error error_code) {
        std::lock_guard<std::mutex> lock(copyrightedMusicEventMutex);
        if (initCallbacks.count(seq) > 0) {
            auto cb = initCallbacks[seq];
            initCallbacks.erase(seq);
            ZEGO_SWITCH_THREAD_PRE
            cb(error_code);
            ZEGO_SWITCH_THREAD_ING
        }
    }

    void zego_on_copyrighted_music_send_extended_request(zego_seq seq, zego_error error_code,
                                                         const char *command, const char *result) {
        std::lock_guard<std::mutex> lock(copyrightedMusicEventMutex);
        if (sendExtendedRequestCallbacks.count(seq) > 0) {
            auto cb = sendExtendedRequestCallbacks[seq];
            sendExtendedRequestCallbacks.erase(seq);
            COPYRIGHTEDMUSIC_COPY_CHAR_TO_STD(command);
            COPYRIGHTEDMUSIC_COPY_CHAR_TO_STD(result);
            ZEGO_SWITCH_THREAD_PRE
            cb(error_code, stdcommand, stdresult);
            ZEGO_SWITCH_THREAD_ING
        }
    }

    void zego_on_copyrighted_music_get_lrc_lyric(zego_seq seq, zego_error error_code,
                                                 const char *lyrics) {
        std::lock_guard<std::mutex> lock(copyrightedMusicEventMutex);
        if (getLrcLyricCallbacks.count(seq) > 0) {
            auto cb = getLrcLyricCallbacks[seq];
            getLrcLyricCallbacks.erase(seq);
            COPYRIGHTEDMUSIC_COPY_CHAR_TO_STD(lyrics);
            ZEGO_SWITCH_THREAD_PRE
            cb(error_code, stdlyrics);
            ZEGO_SWITCH_THREAD_ING
        }
    }

    void zego_on_copyrighted_music_get_krc_lyric_by_token(zego_seq seq, zego_error error_code,
                                                          const char *lyrics) {
        std::lock_guard<std::mutex> lock(copyrightedMusicEventMutex);
        if (getKrcLyricByTokenCallbacks.count(seq) > 0) {
            auto cb = getKrcLyricByTokenCallbacks[seq];
            getKrcLyricByTokenCallbacks.erase(seq);
            COPYRIGHTEDMUSIC_COPY_CHAR_TO_STD(lyrics);
            ZEGO_SWITCH_THREAD_PRE
            cb(error_code, stdlyrics);
            ZEGO_SWITCH_THREAD_ING
        }
    }

    void zego_on_copyrighted_music_request_song(zego_seq seq, zego_error error_code,
                                                const char *resource_id) {
        std::lock_guard<std::mutex> lock(copyrightedMusicEventMutex);
        if (cmOrderSongCallbacks.count(seq) > 0) {
            auto cb = cmOrderSongCallbacks[seq];
            cmOrderSongCallbacks.erase(seq);
            COPYRIGHTEDMUSIC_COPY_CHAR_TO_STD(resource_id);
            ZEGO_SWITCH_THREAD_PRE
            cb(error_code, stdresource_id);
            ZEGO_SWITCH_THREAD_ING
        }
    }

    void zego_on_copyrighted_music_request_accompaniment(zego_seq seq, zego_error error_code,
                                                         const char *resource_id) {
        std::lock_guard<std::mutex> lock(copyrightedMusicEventMutex);
        if (orderAccompanimentCallbacks.count(seq) > 0) {
            auto cb = orderAccompanimentCallbacks[seq];
            orderAccompanimentCallbacks.erase(seq);
            COPYRIGHTEDMUSIC_COPY_CHAR_TO_STD(resource_id);
            ZEGO_SWITCH_THREAD_PRE
            cb(error_code, stdresource_id);
            ZEGO_SWITCH_THREAD_ING
        }
    }

    void zego_on_copyrighted_music_request_accompaniment_clip(zego_seq seq, zego_error error_code,
                                                              const char *resource_id) {
        std::lock_guard<std::mutex> lock(copyrightedMusicEventMutex);
        if (orderAccompanimentClipCallbacks.count(seq) > 0) {
            auto cb = orderAccompanimentClipCallbacks[seq];
            orderAccompanimentClipCallbacks.erase(seq);
            COPYRIGHTEDMUSIC_COPY_CHAR_TO_STD(resource_id);
            ZEGO_SWITCH_THREAD_PRE
            cb(error_code, stdresource_id);
            ZEGO_SWITCH_THREAD_ING
        }
    }

    void zego_on_copyrighted_music_get_music_by_token(zego_seq seq, zego_error error_code,
                                                      const char *resource_id) {
        std::lock_guard<std::mutex> lock(copyrightedMusicEventMutex);
        if (getMusicByTokenCallbacks.count(seq) > 0) {
            auto cb = getMusicByTokenCallbacks[seq];
            getMusicByTokenCallbacks.erase(seq);
            COPYRIGHTEDMUSIC_COPY_CHAR_TO_STD(resource_id);
            ZEGO_SWITCH_THREAD_PRE
            cb(error_code, stdresource_id);
            ZEGO_SWITCH_THREAD_ING
        }
    }

    void zego_on_copyrighted_music_download(zego_seq seq, zego_error error_code) {
        std::lock_guard<std::mutex> lock(copyrightedMusicEventMutex);
        if (loadCallbacks.count(seq) > 0) {
            auto cb = loadCallbacks[seq];
            loadCallbacks.erase(seq);
            ZEGO_SWITCH_THREAD_PRE
            cb(error_code);
            ZEGO_SWITCH_THREAD_ING
        }
    }

    void zego_on_copyrighted_music_get_standard_pitch(zego_seq seq, zego_error error_code,
                                                      const char *pitch) {
        std::lock_guard<std::mutex> lock(copyrightedMusicEventMutex);
        if (getStandardPitchCallbacks.count(seq) > 0) {
            auto cb = getStandardPitchCallbacks[seq];
            getStandardPitchCallbacks.erase(seq);
            COPYRIGHTEDMUSIC_COPY_CHAR_TO_STD(pitch);
            ZEGO_SWITCH_THREAD_PRE
            cb(error_code, stdpitch);
            ZEGO_SWITCH_THREAD_ING
        }
    }

  private:
    std::shared_ptr<IZegoCopyrightedMusicEventHandler> eventHandler;
    std::mutex copyrightedMusicEventMutex;
    std::unordered_map<zego_seq, ZegoCopyrightedMusicInitCallback> initCallbacks;
    std::unordered_map<zego_seq, ZegoCopyrightedMusicSendExtendedRequestCallback>
        sendExtendedRequestCallbacks;
    std::unordered_map<zego_seq, ZegoCopyrightedMusicGetLrcLyricCallback> getLrcLyricCallbacks;
    std::unordered_map<zego_seq, ZegoCopyrightedMusicGetKrcLyricByTokenCallback>
        getKrcLyricByTokenCallbacks;
    std::unordered_map<zego_seq, ZegoCopyrightedMusicRequestSongCallback> cmOrderSongCallbacks;
    std::unordered_map<zego_seq, ZegoCopyrightedMusicRequestAccompanimentCallback>
        orderAccompanimentCallbacks;
    std::unordered_map<zego_seq, ZegoCopyrightedMusicRequestAccompanimentClipCallback>
        orderAccompanimentClipCallbacks;
    std::unordered_map<zego_seq, ZegoCopyrightedMusicGetMusicByTokenCallback>
        getMusicByTokenCallbacks;
    std::unordered_map<zego_seq, ZegoCopyrightedMusicDownloadCallback> loadCallbacks;
    std::unordered_map<zego_seq, ZegoCopyrightedMusicGetStandardPitchCallback>
        getStandardPitchCallbacks;
};

class ZegoExpressCopyrightedMusicContainer {
  public:
    std::recursive_mutex copyrightedMusicMutex;
    std::shared_ptr<ZegoExpressCopyrightedMusicImp> copyrightedMusicInstance = nullptr;
};
#define oCopyrightedMusicContainer                                                                 \
    ZegoSingleton<ZegoExpressCopyrightedMusicContainer>::CreateInstance()
} // namespace EXPRESS
} // namespace ZEGO
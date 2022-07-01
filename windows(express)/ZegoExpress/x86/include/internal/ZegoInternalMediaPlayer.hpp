#pragma once

#include "../ZegoExpressDefines.h"
#include "../ZegoExpressEventHandler.h"
#include "../ZegoExpressInterface.h"

#include "ZegoInternalBase.h"
#include "ZegoInternalBridge.h"

ZEGO_DISABLE_DEPRECATION_WARNINGS

namespace ZEGO {
namespace EXPRESS {

class ZegoExpressMediaPlayerImp : public IZegoMediaPlayer {
  public:
    ZegoExpressMediaPlayerImp(int index) : instanceIndex(index) {}

    void setEventHandler(std::shared_ptr<IZegoMediaPlayerEventHandler> handler) override {
        std::lock_guard<std::mutex> lock(mediaEventMutex);
        mpEventHandler = handler;
    }

    void setVideoHandler(std::shared_ptr<IZegoMediaPlayerVideoHandler> handler,
                         ZegoVideoFrameFormat format) override {
        std::lock_guard<std::mutex> lock(mediaEventMutex);
        if (handler) {
            oInternalOriginBridge->mediaPlayerEnableVideoData(
                true, zego_video_frame_format(format),
                zego_media_player_instance_index(instanceIndex));
        } else {
            oInternalOriginBridge->mediaPlayerEnableVideoData(
                false, zego_video_frame_format(format),
                zego_media_player_instance_index(instanceIndex));
        }
        mpVideoHandler = handler;
    }

    void setAudioHandler(std::shared_ptr<IZegoMediaPlayerAudioHandler> handler) override {
        std::lock_guard<std::mutex> lock(mediaEventMutex);
        if (handler) {
            oInternalOriginBridge->mediaPlayerEnableAudioData(
                true, zego_media_player_instance_index(instanceIndex));
        } else {
            oInternalOriginBridge->mediaPlayerEnableAudioData(
                false, zego_media_player_instance_index(instanceIndex));
        }
        mpAudioHandler = handler;
    }

    void loadResource(const std::string &sourcePath,
                      ZegoMediaPlayerLoadResourceCallback callback) override {
        int seq = oInternalOriginBridge->mediaPlayerPreload(
            sourcePath.c_str(), zego_media_player_instance_index(instanceIndex));
        ZEGO_UNUSED_VARIABLE(seq);
        if (callback != nullptr) {
            std::lock_guard<std::mutex> lock(mediaEventMutex);
            mpLoadResourceCallbacks = callback;
        }
    }

    void loadResourceWithPosition(const std::string &sourcePath, unsigned long long startPosition,
                                  ZegoMediaPlayerLoadResourceCallback callback) override {
        int seq = oInternalOriginBridge->mediaPlayerPreloadWithPosition(
            sourcePath.c_str(), startPosition, zego_media_player_instance_index(instanceIndex));
        ZEGO_UNUSED_VARIABLE(seq);
        if (callback != nullptr) {
            std::lock_guard<std::mutex> lock(mediaEventMutex);
            mpLoadResourceCallbacks = callback;
        }
    }

    void loadResourceFromMediaData(unsigned char *media_data, int media_data_length,
                                   unsigned long long start_position,
                                   ZegoMediaPlayerLoadResourceCallback callback) override {
        int seq = oInternalOriginBridge->mediaPlayerPreload(
            media_data, media_data_length, start_position,
            zego_media_player_instance_index(instanceIndex));
        ZEGO_UNUSED_VARIABLE(seq);
        if (callback != nullptr) {
            std::lock_guard<std::mutex> lock(mediaEventMutex);
            mpLoadResourceCallbacks = callback;
        }
    }

    void loadCopyrightedMusicResourceWithPosition(
        const std::string &resourceId, unsigned long long startPosition,
        ZegoMediaPlayerLoadResourceCallback callback) override {
        int seq = oInternalOriginBridge->mediaPlayerPreloadCopyrightedMusicResourceWithPosition(
            resourceId.c_str(), startPosition, zego_media_player_instance_index(instanceIndex));
        ZEGO_UNUSED_VARIABLE(seq);
        if (callback != nullptr) {
            std::lock_guard<std::mutex> lock(mediaEventMutex);
            mpLoadResourceCallbacks = callback;
        }
    }

    void start() override {
        oInternalOriginBridge->mediaPlayerStart(zego_media_player_instance_index(instanceIndex));
    }

    void stop() override {
        oInternalOriginBridge->mediaPlayerStop(zego_media_player_instance_index(instanceIndex));
    }

    void pause() override {
        oInternalOriginBridge->mediaPlayerPause(zego_media_player_instance_index(instanceIndex));
    }

    void resume() override {
        oInternalOriginBridge->mediaPlayerResume(zego_media_player_instance_index(instanceIndex));
    }

    void seekTo(unsigned long long millisecond, ZegoMediaPlayerSeekToCallback callback) override {
        int seq = oInternalOriginBridge->mediaPlayerSeekTo(
            millisecond, zego_media_player_instance_index(instanceIndex));
        if (callback != nullptr) {
            std::lock_guard<std::mutex> lock(mediaEventMutex);
            mpSeekToCallbacks.insert({seq, callback});
        }
    }

    void enableRepeat(bool enable) override {
        oInternalOriginBridge->mediaPlayerEnableRepeat(
            enable, zego_media_player_instance_index(instanceIndex));
    }

    void setPlayLoopCount(int count) override {
        oInternalOriginBridge->mediaPlayerSetPlayLoopCount(
            count, zego_media_player_instance_index(instanceIndex));
    }

    void setPlaySpeed(float speed) override {
        oInternalOriginBridge->mediaPlayerSetPlaySpeed(
            speed, zego_media_player_instance_index(instanceIndex));
    }

    void enableAux(bool enable) override {
        oInternalOriginBridge->mediaPlayerEnableAUX(
            enable, zego_media_player_instance_index(instanceIndex));
    }

    void muteLocal(bool mute) override {
        oInternalOriginBridge->mediaPlayerMuteLocal(
            mute, zego_media_player_instance_index(instanceIndex));
    }

    void setPlayerCanvas(ZegoCanvas *canvas) override {
        if (canvas == nullptr) {
            oInternalOriginBridge->mediaPlayerSetPlayerCanvas(
                nullptr, zego_media_player_instance_index(instanceIndex));
        } else {
            zego_canvas _canvas;
            _canvas.view = canvas->view;
            _canvas.view_mode = zego_view_mode(canvas->viewMode);
            _canvas.background_color = canvas->backgroundColor;
            oInternalOriginBridge->mediaPlayerSetPlayerCanvas(
                &_canvas, zego_media_player_instance_index(instanceIndex));
        }
    }

    void setVolume(int volume) override {
        oInternalOriginBridge->mediaPlayerSetVolume(
            volume, zego_media_player_instance_index(instanceIndex));
    }

    void setPlayVolume(int volume) override {
        oInternalOriginBridge->mediaPlayerSetPlayVolume(
            volume, zego_media_player_instance_index(instanceIndex));
    }

    void setPublishVolume(int volume) override {
        oInternalOriginBridge->mediaPlayerSetPublishVolume(
            volume, zego_media_player_instance_index(instanceIndex));
    }

    void setProgressInterval(unsigned long long millisecond) override {
        oInternalOriginBridge->mediaPlayerSetProgressInterval(
            millisecond, zego_media_player_instance_index(instanceIndex));
    }

    unsigned long long getTotalDuration() override {
        return oInternalOriginBridge->mediaPlayerGetTotalDuration(
            zego_media_player_instance_index(instanceIndex));
    }

    unsigned long long getCurrentProgress() override {
        return oInternalOriginBridge->mediaPlayerGetCurrentProgress(
            zego_media_player_instance_index(instanceIndex));
    }

    int getPlayVolume() override {
        return oInternalOriginBridge->mediaPlayerGetPlayVolume(
            zego_media_player_instance_index(instanceIndex));
    }

    int getPublishVolume() override {
        return oInternalOriginBridge->mediaPlayerGetPublishVolume(
            zego_media_player_instance_index(instanceIndex));
    }

    ZegoMediaPlayerState getCurrentState() override {
        zego_media_player_state state = oInternalOriginBridge->mediaPlayerGetCurrentState(
            zego_media_player_instance_index(instanceIndex));
        return ZegoMediaPlayerState(state);
    }

    unsigned int getAudioTrackCount() override {
        unsigned int count = oInternalOriginBridge->mediaPlayerGetAudioTrackCount(
            zego_media_player_instance_index(instanceIndex));
        return count;
    }

    void setAudioTrackIndex(unsigned int index) override {
        oInternalOriginBridge->mediaPlayerSetAudioTrackIndex(
            index, zego_media_player_instance_index(instanceIndex));
    }

    void setVoiceChangerParam(ZegoMediaPlayerAudioChannel audioChannel,
                              ZegoVoiceChangerParam param) override {
        oInternalOriginBridge->mediaPlayerSetVoiceChangerParam(
            zego_media_player_audio_channel(audioChannel), param.pitch,
            zego_media_player_instance_index(instanceIndex));
    }

    int getIndex() override { return instanceIndex; }

    void takeSnapshot(ZegoMediaPlayerTakeSnapshotCallback callback) override {
        oInternalOriginBridge->takeSnapshot(zego_media_player_instance_index(instanceIndex));
        if (callback != nullptr) {
            std::lock_guard<std::mutex> lock(mediaEventMutex);
            mpTakeSnapshotCallback = callback;
        }
    }

    void enableAccurateSeek(bool enable, ZegoAccurateSeekConfig *config) override {
        zego_accurate_seek_config _zego_accurate_seek_config;
        memset(&_zego_accurate_seek_config, 0, sizeof(zego_accurate_seek_config));
        if (config == nullptr) {
            _zego_accurate_seek_config.time_out = 5000;

        } else {
            _zego_accurate_seek_config.time_out = config->timeout;
        }
        oInternalOriginBridge->mediaPlayerEnableAccurateSeek(
            enable, &_zego_accurate_seek_config, zego_media_player_instance_index(instanceIndex));
    }

    void setNetWorkResourceMaxCache(unsigned int time, unsigned int size) override {
        oInternalOriginBridge->mediaPlayerSetNetWorkResourceMaxCache(
            time, size, zego_media_player_instance_index(instanceIndex));
    };

    ZegoNetWorkResourceCache *getNetWorkResourceCache() override {
        zego_network_resource_cache network_resource_cache;
        memset(&network_resource_cache, 0, sizeof(zego_network_resource_cache));
        oInternalOriginBridge->mediaPlayerGetNetWorkResourceCache(
            &network_resource_cache, zego_media_player_instance_index(instanceIndex));
        ZegoNetWorkResourceCache *cache_result = new ZegoNetWorkResourceCache();
        cache_result->size = network_resource_cache.size;
        cache_result->time = network_resource_cache.time;
        return cache_result;
    };

    void setNetWorkBufferThreshold(unsigned int threshold) override {
        oInternalOriginBridge->mediaPlayerSetNetWorkBufferThreshold(
            threshold, zego_media_player_instance_index(instanceIndex));
    }

    void enableSoundLevelMonitor(bool enable, unsigned int millisecond) override {
        oInternalOriginBridge->mediaPlayerEnableSoundLevelMonitor(
            enable, millisecond, zego_media_player_instance_index(instanceIndex));
    }

    void enableFrequencySpectrumMonitor(bool enable, unsigned int millisecond) override {
        oInternalOriginBridge->mediaPlayerEnableFrequencySpectrumMonitor(
            enable, millisecond, zego_media_player_instance_index(instanceIndex));
    }

    void setActiveAudioChannel(ZegoMediaPlayerAudioChannel audioChannel) override {
        oInternalOriginBridge->mediaPlayerSetActiveAudioChannel(
            zego_media_player_audio_channel(audioChannel),
            zego_media_player_instance_index(instanceIndex));
    }

    void clearView() override {
        oInternalOriginBridge->mediaPlayerClearView(
            zego_media_player_instance_index(instanceIndex));
    }

    void zego_on_media_player_state_update(zego_media_player_state state, zego_error error_code) {
        std::lock_guard<std::mutex> lock(mediaEventMutex);
        if (mpEventHandler) {
            auto weakMPEventHandler = std::weak_ptr<IZegoMediaPlayerEventHandler>(mpEventHandler);
            ZEGO_SWITCH_THREAD_PRE
            auto handlerInMain = weakMPEventHandler.lock();
            if (handlerInMain) {
                handlerInMain->onMediaPlayerStateUpdate(this, ZegoMediaPlayerState(state),
                                                        error_code);
            }
            ZEGO_SWITCH_THREAD_ING
        }
    }

    void zego_on_media_player_network_event(zego_media_player_network_event event) {
        std::lock_guard<std::mutex> lock(mediaEventMutex);
        auto weakMPEventHandler = std::weak_ptr<IZegoMediaPlayerEventHandler>(mpEventHandler);
        ZEGO_SWITCH_THREAD_PRE
        auto handlerInMain = weakMPEventHandler.lock();
        if (handlerInMain) {
            handlerInMain->onMediaPlayerNetworkEvent(this, ZegoMediaPlayerNetworkEvent(event));
        }
        ZEGO_SWITCH_THREAD_ING
    }

    void zego_on_media_player_playing_progress(unsigned long long millisecond) {
        std::lock_guard<std::mutex> lock(mediaEventMutex);
        auto weakMPEventHandler = std::weak_ptr<IZegoMediaPlayerEventHandler>(mpEventHandler);
        ZEGO_SWITCH_THREAD_PRE
        auto handlerInMain = weakMPEventHandler.lock();
        if (handlerInMain) {
            handlerInMain->onMediaPlayerPlayingProgress(this, millisecond);
        }
        ZEGO_SWITCH_THREAD_ING
    }

    void zego_on_media_player_recv_sei(const unsigned char *data, unsigned int data_length) {
        std::vector<unsigned char> seiData;
        seiData.reserve(data_length);
        for (unsigned int i = 0; i < data_length; i++) {
            seiData.push_back(data[i]);
        }

        std::lock_guard<std::mutex> lock(mediaEventMutex);
        auto weakMPEventHandler = std::weak_ptr<IZegoMediaPlayerEventHandler>(mpEventHandler);
        ZEGO_SWITCH_THREAD_PRE
        auto handlerInMain = weakMPEventHandler.lock();
        if (handlerInMain) {
            handlerInMain->onMediaPlayerRecvSEI(this, seiData.data(), data_length);
        }
        ZEGO_SWITCH_THREAD_ING
    }

    void zego_on_media_player_sound_level_update(float sound_level) {
        std::lock_guard<std::mutex> lock(mediaEventMutex);
        auto weakMPEventHandler = std::weak_ptr<IZegoMediaPlayerEventHandler>(mpEventHandler);
        ZEGO_SWITCH_THREAD_PRE
        auto handlerInMain = weakMPEventHandler.lock();
        if (handlerInMain) {
            handlerInMain->onMediaPlayerSoundLevelUpdate(this, sound_level);
        }
        ZEGO_SWITCH_THREAD_ING
    }

    void zego_on_media_player_frequency_spectrum_update(float *spectrum_list,
                                                        unsigned int spectrum_count) {
        ZegoAudioSpectrum spectrumList;
        for (unsigned int i = 0; i < spectrum_count; i++) {
            spectrumList.push_back(spectrum_list[i]);
        }
        std::lock_guard<std::mutex> lock(mediaEventMutex);
        auto weakMPEventHandler = std::weak_ptr<IZegoMediaPlayerEventHandler>(mpEventHandler);
        ZEGO_SWITCH_THREAD_PRE
        auto handlerInMain = weakMPEventHandler.lock();
        if (handlerInMain) {
            handlerInMain->onMediaPlayerFrequencySpectrumUpdate(this, spectrumList);
        }
        ZEGO_SWITCH_THREAD_ING
    }

    void zego_on_mediaplayer_seek_to_result(zego_seq seq, zego_error error_code) {
        std::lock_guard<std::mutex> lock(mediaEventMutex);
        if (mpSeekToCallbacks.count(seq) > 0) {
            auto cb = mpSeekToCallbacks[seq];
            mpSeekToCallbacks.erase(seq);
            ZEGO_SWITCH_THREAD_PRE
            cb(error_code);
            ZEGO_SWITCH_THREAD_ING
        }
    }

    void zego_on_mediaplayer_load_file_result(zego_error error_code) {
        std::lock_guard<std::mutex> lock(mediaEventMutex);
        if (mpLoadResourceCallbacks) {
            ZEGO_SWITCH_THREAD_PRE
            mpLoadResourceCallbacks(error_code);
            ZEGO_SWITCH_THREAD_ING
        }
    }

    void zego_on_media_player_video_frame(const unsigned char **data, unsigned int *data_length,
                                          const struct zego_video_frame_param _param,
                                          const char *extra_info) {
        std::lock_guard<std::mutex> lock(mediaEventMutex);
        if (mpVideoHandler) {
            auto param = ZegoExpressConvert::I2OVideoFrameParam(_param);
            mpVideoHandler->onVideoFrame(this, data, data_length, param);
            mpVideoHandler->onVideoFrame(this, data, data_length, param, extra_info);
        }
    }

    void zego_on_media_player_take_snapshot_result(
        zego_error error_code, void *image, enum zego_media_player_instance_index instance_index) {
        std::lock_guard<std::mutex> lock(mediaEventMutex);
        if (mpTakeSnapshotCallback) {
            mpTakeSnapshotCallback(error_code, image);
        }
    }

    void zego_on_media_player_audio_frame(const unsigned char *data, unsigned int data_length,
                                          const struct zego_audio_frame_param _param) {
        std::lock_guard<std::mutex> lock(mediaEventMutex);
        if (mpAudioHandler) {
            ZegoAudioFrameParam param;
            param.channel = ZegoAudioChannel(_param.channel);
            param.sampleRate = ZegoAudioSampleRate(_param.sample_rate);
            mpAudioHandler->onAudioFrame(this, data, data_length, param);
        }
    }

  private:
    std::shared_ptr<IZegoMediaPlayerVideoHandler> mpVideoHandler;
    std::shared_ptr<IZegoMediaPlayerEventHandler> mpEventHandler;
    std::shared_ptr<IZegoMediaPlayerAudioHandler> mpAudioHandler;
    ZegoMediaPlayerLoadResourceCallback mpLoadResourceCallbacks;
    ZegoMediaPlayerTakeSnapshotCallback mpTakeSnapshotCallback;
    std::unordered_map<zego_seq, ZegoMediaPlayerSeekToCallback> mpSeekToCallbacks;
    std::mutex mediaEventMutex;
    int instanceIndex = -1;
};

} // namespace EXPRESS
} // namespace ZEGO

ZEGO_ENABLE_DEPRECATION_WARNINGS


#ifndef __ZEGO_EXPRESS_UTILITIES_H__
#define __ZEGO_EXPRESS_UTILITIES_H__

#include "zego-express-defines.h"

ZEGO_BEGIN_DECLS
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
ZEGOEXP_API zego_error EXP_CALL zego_express_start_performance_monitor(unsigned int millisecond);

/// Stop system performance monitoring.
///
/// Available since: 1.19.0
/// Description: Stop system performance monitoring. After the monitoring is stopped, the [onPerformanceStatusUpdate] callback will not triggered.
/// Use cases: Monitor system performance can help user quickly locate and solve performance problems and improve user experience.
/// When to call: It needs to be called after [createEngine].
/// Restrictions: None.
/// Related APIs: Call [startPerformanceMonitor] to start system performance monitoring.
ZEGOEXP_API zego_error EXP_CALL zego_express_stop_performance_monitor();

/// Start network probe.
///
/// Available since: 2.3.0
/// Description: Some local network problems may cause audio and video calls to fail. Using this function to probe the network protocols, assist in locating and solving related network problems.
/// Use cases: Before pushing and pulling the stream, detect and locate some possible network problems.
/// When to call: It needs to be called after [createEngine].
/// Restrictions: The SDK will not perform multiple network probe at the same time, that is, if the network probe is in progress, the SDK will ignore subsequent calls of this function.
/// Caution: The SDK detects http, tcp, and udp in sequence internally. If the probe fails in the middle, the subsequent detection will not continue. Therefore, when reading the values ​​in the probe result, please pay attention to check if the value is NULL. Network probe may take a long time. Developers can call [stopNetworkProbe] to stop network probe if needed. It is not recommended to start network probe during publishing/playing stream.
/// Related APIs: Call [stopNetworkProbe] to stop network probe.
///
/// @param config network probe config.
ZEGOEXP_API zego_seq EXP_CALL
zego_express_start_network_probe(struct zego_network_probe_config config);

/// Stop network probe.
///
/// Available since: 2.3.0
/// Description: Stop network probe.
/// Use cases: Before pushing and pulling the stream, detect and locate some possible network problems.
/// When to call: It needs to be called after [createEngine].
/// Restrictions: None.
/// Related APIs: Call [startNetworkProbe] to start network probe.
ZEGOEXP_API zego_error EXP_CALL zego_express_stop_network_probe();

/// Test network connectivity.
///
/// Test network connectivity.
ZEGOEXP_API zego_seq EXP_CALL zego_express_test_network_connectivity();

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
ZEGOEXP_API zego_error EXP_CALL zego_express_start_network_speed_test(
    struct zego_network_speed_test_config config, unsigned int interval);

/// Stop network speed test.
///
/// Available since: 1.20.0
/// Description: Stop network speed test.
/// Use cases: This function can be used to detect whether the network environment is suitable for pushing/pulling streams with specified bitrates.
/// When to call: It needs to be called after [createEngine].
/// Restrictions: None.
/// Caution: After the network speed test stopped, [onNetworkSpeedTestQualityUpdate] callback will not be triggered.
/// Related APIs: Call [startNetworkSpeedTest] to start network speed test.
ZEGOEXP_API zego_error EXP_CALL zego_express_stop_network_speed_test();

/// Obtain synchronization network time information.
///
/// Available since: 2.9.0
/// Description: Obtain synchronization network time(NTP), including timestamp and maximum deviation.
/// Use cases: When performing multi-terminal synchronization behaviors, network time synchronization is required.
/// When to call: It needs to be called after [createEngine].
/// Restrictions: None.
ZEGOEXP_API zego_error EXP_CALL
zego_express_get_network_time_info(zego_network_time_info *time_info);

/// System performance monitoring callback.
///
/// Available since: 1.19.0
/// Description: System performance monitoring callback. The callback notification period is the value of millisecond parameter set by call [startPerformanceMonitor].
/// Use cases: Monitor system performance can help user quickly locate and solve performance problems and improve user experience.
/// When to trigger: It will triggered after [createEngine], and call [startPerformanceMonitor] to start system performance monitoring.
/// Restrictions: None.
///
/// @param status System performance monitoring status.
/// @param user_context Context of user.
typedef void (*zego_on_performance_status_update)(struct zego_performance_status status,
                                                  void *user_context);

ZEGOEXP_API void EXP_CALL zego_register_performance_status_update_callback(
    zego_on_performance_status_update callback_func, void *user_context);

/// Network mode changed callback.
///
/// Available since: 1.20.0
/// Description: Network mode changed callback.
/// When to trigger: This callback will be triggered when the device's network mode changed, such as switched from WiFi to 5G, or when network is disconnected.
/// Restrictions: None.
///
/// @param mode Current network mode.
/// @param user_context Context of user.
typedef void (*zego_on_network_mode_changed)(enum zego_network_mode mode, void *user_context);

ZEGOEXP_API void EXP_CALL zego_register_network_mode_changed_callback(
    zego_on_network_mode_changed callback_func, void *user_context);

/// Network speed test error callback.
///
/// Available since: 1.20.0
/// Description: Network speed test error callback.
/// Use cases: This function can be used to detect whether the network environment is suitable for pushing/pulling streams with specified bitrates.
/// When to Trigger: If an error occurs during the speed test, such as: can not connect to speed test server, this callback will be triggered.
/// Restrictions: None.
///
/// @param error_code Network speed test error code. Please refer to error codes document https://docs.zegocloud.com/en/5548.html for details.
/// @param type Uplink or downlink.
/// @param user_context Context of user.
typedef void (*zego_on_network_speed_test_error)(int error_code,
                                                 enum zego_network_speed_test_type type,
                                                 void *user_context);

ZEGOEXP_API void EXP_CALL zego_register_network_speed_test_error_callback(
    zego_on_network_speed_test_error callback_func, void *user_context);

/// Network speed test quality callback.
///
/// Available since: 1.20.0
/// Description: Network speed test quality callback.
/// Use cases: This function can be used to detect whether the network environment is suitable for pushing/pulling streams with specified bitrates.
/// When to Trigger: After call [startNetworkSpeedTest] start network speed test, this callback will be triggered. The trigger period is determined by the parameter value specified by call [startNetworkSpeedTest], default value is 3 seconds
/// Restrictions: None.
/// Caution: When error occurred during network speed test or [stopNetworkSpeedTest] called, this callback will not be triggered.
///
/// @param quality Network speed test quality.
/// @param type Uplink or downlink.
/// @param user_context Context of user.
typedef void (*zego_on_network_speed_test_quality_update)(
    const struct zego_network_speed_test_quality quality, enum zego_network_speed_test_type type,
    void *user_context);

ZEGOEXP_API void EXP_CALL zego_register_network_speed_test_quality_update_callback(
    zego_on_network_speed_test_quality_update callback_func, void *user_context);

/// Callback for test network connectivity.
///
/// @param seq Sequence.
/// @param error_code Error code, please refer to the error codes document https://docs.zegocloud.com/en/5548.html for details.
/// @param result Network connectivity test results
/// @param user_context Context of user.
typedef void (*zego_on_test_network_connectivity)(
    zego_seq seq, zego_error error_code, const struct zego_test_network_connectivity_result result,
    void *user_context);

ZEGOEXP_API void EXP_CALL zego_register_test_network_connectivity_callback(
    zego_on_test_network_connectivity callback_func, void *user_context);

/// Callback for network probe.
///
/// @param seq Sequence.
/// @param error_code Error code, please refer to the error codes document https://docs.zegocloud.com/en/5548.html for details.
/// @param result Network probe result
/// @param user_context Context of user.
typedef void (*zego_on_network_probe_result)(zego_seq seq, zego_error error_code,
                                             const struct zego_network_probe_result result,
                                             void *user_context);

ZEGOEXP_API void EXP_CALL zego_register_network_probe_result_callback(
    zego_on_network_probe_result callback_func, void *user_context);

ZEGO_END_DECLS

#endif

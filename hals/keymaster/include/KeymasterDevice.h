/*
 * Copyright 2017, The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef ANDROID_HARDWARE_KEYMASTER_KEYMASTER_DEVICE_H
#define ANDROID_HARDWARE_KEYMASTER_KEYMASTER_DEVICE_H

#include <android/hardware/keymaster/3.0/IKeymasterDevice.h>

#include <Keymaster.client.h>

namespace android {
namespace hardware {
namespace keymaster {

using ::android::hardware::keymaster::V3_0::ErrorCode;
using ::android::hardware::keymaster::V3_0::IKeymasterDevice;
using ::android::hardware::keymaster::V3_0::KeyFormat;
using ::android::hardware::keymaster::V3_0::KeyParameter;
using ::android::hardware::keymaster::V3_0::KeyPurpose;
using ::android::hardware::Return;
using ::android::hardware::hidl_vec;

using KeymasterClient = ::nugget::app::keymaster::IKeymaster;

struct KeymasterDevice : public IKeymasterDevice {
    KeymasterDevice(KeymasterClient& keymaster) : _keymaster{keymaster} {}
    ~KeymasterDevice() override = default;

    // Methods from ::android::hardware::keymaster::V3_0::IKeymasterDevice follow.
    Return<void> getHardwareFeatures(getHardwareFeatures_cb _hidl_cb);
    Return<ErrorCode> addRngEntropy(const hidl_vec<uint8_t>& data) override;
    Return<void> generateKey(const hidl_vec<KeyParameter>& keyParams,
                             generateKey_cb _hidl_cb) override;
    Return<void> getKeyCharacteristics(const hidl_vec<uint8_t>& keyBlob,
                                       const hidl_vec<uint8_t>& clientId,
                                       const hidl_vec<uint8_t>& appData,
                                       getKeyCharacteristics_cb _hidl_cb) override;
    Return<void> importKey(const hidl_vec<KeyParameter>& params, KeyFormat keyFormat,
                           const hidl_vec<uint8_t>& keyData, importKey_cb _hidl_cb) override;
    Return<void> exportKey(KeyFormat exportFormat, const hidl_vec<uint8_t>& keyBlob,
                           const hidl_vec<uint8_t>& clientId, const hidl_vec<uint8_t>& appData,
                           exportKey_cb _hidl_cb) override;
    Return<void> attestKey(const hidl_vec<uint8_t>& keyToAttest,
                           const hidl_vec<KeyParameter>& attestParams,
                           attestKey_cb _hidl_cb) override;
    Return<void> upgradeKey(const hidl_vec<uint8_t>& keyBlobToUpgrade,
                            const hidl_vec<KeyParameter>& upgradeParams,
                            upgradeKey_cb _hidl_cb) override;
    Return<ErrorCode> deleteKey(const hidl_vec<uint8_t>& keyBlob) override;
    Return<ErrorCode> deleteAllKeys() override;
    Return<ErrorCode> destroyAttestationIds() override;
    Return<void> begin(KeyPurpose purpose, const hidl_vec<uint8_t>& key,
                       const hidl_vec<KeyParameter>& inParams, begin_cb _hidl_cb) override;
    Return<void> update(uint64_t operationHandle, const hidl_vec<KeyParameter>& inParams,
                        const hidl_vec<uint8_t>& input, update_cb _hidl_cb) override;
    Return<void> finish(uint64_t operationHandle, const hidl_vec<KeyParameter>& inParams,
                        const hidl_vec<uint8_t>& input, const hidl_vec<uint8_t>& signature,
                        finish_cb _hidl_cb) override;
    Return<ErrorCode> abort(uint64_t operationHandle) override;

private:
    KeymasterClient& _keymaster;
};

}  // namespace keymaster
}  // namespace hardware
}  // namespace android

#endif // ANDROID_HARDWARE_KEYMASTER_KEYMASTER_DEVICE_H

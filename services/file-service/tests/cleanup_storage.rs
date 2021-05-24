//
// Copyright (C) 2018 Kubos Corporation
//
// Licensed under the Apache License, Version 2.0 (the "License")
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//

mod common;

use crate::common::*;
use cubeos_system::Config as ServiceConfig;
use file_service::recv_loop;
use std::fs;
use std::thread;
use std::time::Duration;
use tempfile::TempDir;

// Request a cleanup of whole remote temp storage
#[test]
fn cleanup_storage_dir() {
    let test_dir = TempDir::new().expect("Failed to create test dir");
    let test_dir_str = test_dir.path().to_str().unwrap();
    let source = format!("{}/source", test_dir_str);
    let dest = format!("{}/dest", test_dir_str);
    let service_port = 8001;
    let downlink_port = 7001;

    let contents = [2; 5000];

    let _hash = create_test_file(&source, &contents);

    let storage_dir = format!("{}/service", test_dir_str);
    service_new!(service_port, downlink_port, 4096, storage_dir);

    // Download a partial file so that we can resume the download later
    let _result = download(
        "127.0.0.1",
        downlink_port,
        &format!("127.0.0.1:{}", service_port),
        &source,
        &dest,
        Some(format!("{}/client", test_dir_str)),
        4096,
    );

    // Storage directory should still exist after successful transfer
    assert!(fs::read_dir(format!("{}/service/storage", test_dir_str)).is_ok());

    cleanup(
        "127.0.0.1",
        downlink_port,
        &format!("127.0.0.1:{}", service_port),
        None,
        Some(format!("{}/client", test_dir_str)),
        4069,
    )
    .unwrap();

    // Storage directory should be gone after request for cleanup
    assert!(fs::read_dir(format!("{}/service/storage", test_dir_str)).is_err());
}

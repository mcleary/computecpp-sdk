/***************************************************************************
*
*  Copyright (C) 2016-2018 Codeplay Software Limited
*  Licensed under the Apache License, Version 2.0 (the "License");
*  you may not use this file except in compliance with the License.
*  You may obtain a copy of the License at
*
*      http://www.apache.org/licenses/LICENSE-2.0
*
*  For your convenience, a copy of the License has been included in this
*  repository.
*
*  Unless required by applicable law or agreed to in writing, software
*  distributed under the License is distributed on an "AS IS" BASIS,
*  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
*  See the License for the specific language governing permissions and
*  limitations under the License.
*
*  Codeplay's ComputeCpp SDK
*
*  query-system-info.cpp
*
*  Description:
*    Sample code that illustrates how to query and get information about
*    the available SYCL platforms.
*
**************************************************************************/

#include <CL/sycl.hpp>
#include <SYCL/platform.h>

#include <iostream>
#include <numeric>

std::ostream& operator<< (std::ostream& out, cl::sycl::info::device_type device_type)
{  
    switch (device_type)
    {
        case cl::sycl::info::device_type::cpu:
            out << "CPU";
            break;
        case cl::sycl::info::device_type::gpu:
            out << "GPU";
            break;
        case cl::sycl::info::device_type::accelerator:
            out << "Accelerator";
            break;
        case cl::sycl::info::device_type::custom:
            out << "Custom";
            break;
        case cl::sycl::info::device_type::automatic:
            out << "Automatic";
            break;
        case cl::sycl::info::device_type::host:
            out << "Host";
            break;
        case cl::sycl::info::device_type::all:
            out << "All";
            break;
        default:
            break;
    };

    return out;
}

void f(bool a)
{

}

int main()
{
    // Query the available platforms
    const auto platforms = cl::sycl::platform::get_platforms();

    std::cout << "Available Platforms:" << std::endl;
    for (const auto &platform : platforms)
    {        
        std::cout << "\tName: " << platform.get_info<cl::sycl::info::platform::name>() << std::endl;        
        std::cout << "\tVendor: " << platform.get_info<cl::sycl::info::platform::vendor>() << std::endl;
        std::cout << "\tProfile: " << platform.get_info<cl::sycl::info::platform::profile>() << std::endl;
        std::cout << "\tVersion: " << platform.get_info<cl::sycl::info::platform::version>() << std::endl;

        const auto extensions = platform.get_info<cl::sycl::info::platform::extensions>();        
        const auto extensionsStr = std::accumulate(std::begin(extensions), std::end(extensions), std::string{}, [=](std::string accumulated, std::string extension)
        {
            return accumulated.empty() ? extension : accumulated + ", " + extension;
        });

        std::cout << "\tExtensions: " << extensionsStr << std::endl;

        const auto devices = platform.get_devices();

        std::cout << "\tNumber of devices: " << devices.size() << std::endl;

        std::cout << std::endl;

        std::cout << "\tDevices:" << std::endl;

        for (auto device : devices)
        {
            auto a = device.get_info<cl::sycl::info::device::queue_profiling>();
            f(a);

            std::cout << "\t\tType: " << device.get_info<cl::sycl::info::device::device_type>() << std::endl;
            std::cout << "\t\tVendor ID: " << device.get_info<cl::sycl::info::device::vendor_id>() << std::endl;
            std::cout << "\t\tMax Compute Units: " << device.get_info<cl::sycl::info::device::max_compute_units>() << std::endl;
            std::cout << "\t\tMax Work Item Dimensions: " << device.get_info<cl::sycl::info::device::max_work_item_dimensions>() << std::endl;
            std::cout << "\t\tQueue Profiling: " << device.get_info<cl::sycl::info::device::queue_profiling>() << std::endl;

            std::cout << std::endl;
        }

        std::cout << std::endl;
    }

    return 0;
}

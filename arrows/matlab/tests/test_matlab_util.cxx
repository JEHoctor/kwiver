/*ckwg +29
 * Copyright 2016 by Kitware, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *  * Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 *  * Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 *  * Neither name of Kitware, Inc. nor the names of any contributors may be used
 *    to endorse or promote products derived from this software without specific
 *    prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHORS OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * \file
 * \brief test detected_object class
 */

#include <test_common.h>

#include <vital/types/detected_object.h>
#include <arrows/matlab/matlab_util.h>
#include <arrows/ocv/image_container.h>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#define TEST_ARGS ( kwiver::vital::path_t const &data_dir )

DECLARE_TEST_MAP();

int
main(int argc, char** argv)
{
  CHECK_ARGS(2);

  testname_t const testname = argv[1];
  kwiver::vital::path_t data_dir( argv[2] );

  RUN_TEST(testname, data_dir);
}


// ------------------------------------------------------------------
IMPLEMENT_TEST(image_conversion)
{
  kwiver::vital::path_t test_read_file = data_dir + "/test_kitware_logo.jpg";

  cv::Mat ocv_image;
  ocv_image = cv::imread(test_read_file, CV_LOAD_IMAGE_COLOR);   // Read the file
  if(! ocv_image.data )                              // Check for invalid input
  {
    TEST_ERROR( "Could not open or find the image" );
    return;
  }

  auto ic_sptr = std::make_shared< kwiver::arrows::ocv::image_container >( ocv_image );

  cv::namedWindow( "input OCV image", cv::WINDOW_AUTOSIZE ); // Create a window for display.
  cv::imshow( "input OCV image", ocv_image ); // Show our image inside it.
  cv::waitKey( 000 ); // pause for keystroke

  kwiver::arrows::matlab::MxArraySptr mx_image = kwiver::arrows::matlab::convert_mx_image( ic_sptr );

  auto ocv_ic = kwiver::arrows::matlab::convert_mx_image( mx_image );

  cv::namedWindow( "output OCV image", cv::WINDOW_AUTOSIZE ); // Create a window for display.
  cv::imshow( "output OCV image", ocv_image ); // Show our image inside it.
  cv::waitKey( 000 ); // pause for keystroke
}
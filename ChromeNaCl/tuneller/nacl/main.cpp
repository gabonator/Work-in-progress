// Copyright (c) 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include <stdio.h>
#include <stdlib.h>
#include <cmath>

#include "ppapi/c/ppb_image_data.h"
#include "ppapi/cpp/graphics_2d.h"
#include "ppapi/cpp/image_data.h"
#include "ppapi/cpp/input_event.h"
#include "ppapi/cpp/instance.h"
#include "ppapi/cpp/module.h"
#include "ppapi/cpp/point.h"
#include "ppapi/cpp/audio.h"
#include "ppapi/utility/completion_callback_factory.h"

#ifdef WIN32
#undef PostMessage
// Allow 'this' in initializer list
#pragma warning(disable : 4355)
#endif

#include "glue.h"

class Graphics2DInstance : public pp::Instance
{
 public:
  explicit Graphics2DInstance(PP_Instance instance)
      : pp::Instance(instance),
        callback_factory_(this),
        buffer_(NULL),
        device_scale_(1.0f) 
  {
  }

  ~Graphics2DInstance() 
  { 
    delete[] buffer_; 
  }

  virtual bool Init(uint32_t argc, const char* argn[], const char* argv[]) 
  {
    RequestInputEvents(PP_INPUTEVENT_CLASS_TOUCH);
    RequestFilteringInputEvents(PP_INPUTEVENT_CLASS_KEYBOARD);

    return true;
  }

  virtual void DidChangeView(const pp::View& view) 
  {
    device_scale_ = view.GetDeviceScale();
    pp::Size new_size = pp::Size(view.GetRect().width() * device_scale_,
                                 view.GetRect().height() * device_scale_);

    if (!CreateContext(new_size))
      return;

    // When flush_context_ is null, it means there is no Flush callback in
    // flight. This may have happened if the context was not created
    // successfully, or if this is the first call to DidChangeView (when the
    // module first starts). In either case, start the main loop.
    if (flush_context_.is_null())
      MainLoop(0);
  }

  virtual bool HandleInputEvent(const pp::InputEvent& event) 
  {
    if (!buffer_)
      return true;

    if ( event.GetType() == PP_INPUTEVENT_TYPE_KEYDOWN )
    {
      pp::KeyboardInputEvent key_event(event);
      mainKey(key_event.GetKeyCode(), 1);
    }

    if ( event.GetType() == PP_INPUTEVENT_TYPE_KEYUP )
    {
      pp::KeyboardInputEvent key_event(event);
      mainKey(key_event.GetKeyCode(), 0);
    }
    return true;
  }

 private:

  bool CreateContext(const pp::Size& new_size) 
  {
    const bool kIsAlwaysOpaque = true;
    context_ = pp::Graphics2D(this, new_size, kIsAlwaysOpaque);
    // Call SetScale before BindGraphics so the image is scaled correctly on
    // HiDPI displays.
    context_.SetScale(1.0f / device_scale_);
    if (!BindGraphics(context_)) {
      fprintf(stderr, "Unable to bind 2d context!\n");
      context_ = pp::Graphics2D();
      return false;
    }

    // Allocate a buffer of palette entries of the same size as the new context.
    buffer_ = new uint8_t[new_size.width() * new_size.height()];
    size_ = new_size;

    return true;
  }

  void Paint() 
  {
    // See the comment above the call to ReplaceContents below.
    PP_ImageDataFormat format = pp::ImageData::GetNativeImageDataFormat();
    const bool kDontInitToZero = false;
    pp::ImageData image_data(this, format, size_, kDontInitToZero);

    uint32_t* data = static_cast<uint32_t*>(image_data.data());
    if (!data)
      return;


    static bool bFirst = true;
    if ( bFirst )
    {
      bFirst = false;
      mainInit(size_.width(), size_.height());
    }

    mainProc(data, size_.width(), size_.height());

    // Using Graphics2D::ReplaceContents is the fastest way to update the
    // entire canvas every frame. According to the documentation:
    //
    //   Normally, calling PaintImageData() requires that the browser copy
    //   the pixels out of the image and into the graphics context's backing
    //   store. This function replaces the graphics context's backing store
    //   with the given image, avoiding the copy.
    //
    //   In the case of an animation, you will want to allocate a new image for
    //   the next frame. It is best if you wait until the flush callback has
    //   executed before allocating this bitmap. This gives the browser the
    //   option of caching the previous backing store and handing it back to
    //   you (assuming the sizes match). In the optimal case, this means no
    //   bitmaps are allocated during the animation, and the backing store and
    //   "front buffer" (which the module is painting into) are just being
    //   swapped back and forth.
    //
    context_.ReplaceContents(&image_data);
  }

  void MainLoop(int32_t) 
  {
    if (context_.is_null()) {
      // The current Graphics2D context is null, so updating and rendering is
      // pointless. Set flush_context_ to null as well, so if we get another
      // DidChangeView call, the main loop is started again.
      flush_context_ = context_;
      return;
    }

    Paint();

    // Store a reference to the context that is being flushed; this ensures
    // the callback is called, even if context_ changes before the flush
    // completes.
    flush_context_ = context_;
    context_.Flush(
        callback_factory_.NewCallback(&Graphics2DInstance::MainLoop));
  }

  pp::CompletionCallbackFactory<Graphics2DInstance> callback_factory_;
  pp::Graphics2D context_;
  pp::Graphics2D flush_context_;
  pp::Size size_;
  uint8_t* buffer_;
  float device_scale_;
};

class Graphics2DModule : public pp::Module {
 public:
  Graphics2DModule() : pp::Module() {}
  virtual ~Graphics2DModule() {}

  virtual pp::Instance* CreateInstance(PP_Instance instance) {
    return new Graphics2DInstance(instance);
  }
};

namespace pp {
  Module* CreateModule() 
  { 
    return new Graphics2DModule(); 
  }
}  // namespace pp


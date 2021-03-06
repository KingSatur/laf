// LAF OS Library
// Copyright (C) 2015  David Capello
//
// This file is released under the terms of the MIT license.
// Read LICENSE.txt for more information.

class OSXWindowImpl;

@interface OSXWindowDelegate : NSObject {
@private
  OSXWindowImpl* m_impl;
}
@end

@implementation OSXWindowDelegate

- (OSXWindowDelegate*)initWithWindowImpl:(OSXWindowImpl*)impl
{
  m_impl = impl;
  return self;
}

- (BOOL)windowShouldClose:(id)sender
{
  os::Event ev;
  ev.setType(os::Event::CloseDisplay);
  //ev.setDisplay(nullptr);             // TODO
  os::queue_event(ev);
  return NO;
}

- (void)windowWillClose:(NSNotification*)notification
{
  m_impl->onClose();
}

- (void)windowWillStartLiveResize:(NSNotification*)notification
{
  m_impl->onStartResizing();
}

- (void)windowDidEndLiveResize:(NSNotification*)notification
{
  m_impl->onEndResizing();
}

- (void)windowDidMiniaturize:(NSNotification*)notification
{
}

@end

/* This nonsense was written by Andrew Nowak <andrew@nowak.me.uk>, 2019.  It
 * was based on the challenge set by Julia Evans, which can be found at
 * <https://jvns.ca/blog/2019/11/25/challenge--make-a-bouncy-window-manager/>,
 * and TinyWM, which was written by Nick Welch <mack@incise.org>, 2005, and can
 * itself be found at <http://incise.org/tinywm.html>
 *
 * That (TinyWM) software is in the public domain and is provided AS IS, with
 * NO WARRANTY.
 */

#include <X11/Xlib.h>
#include <stdio.h>
#include <unistd.h>

int corners(XWindowAttributes* attr, XWindowAttributes* root_attr) {
  // top left
  if (attr->x == 0 && attr->y == 0)
    return 1;
  // bottom left
  if (attr->x == 0 && attr->y + attr->height == root_attr->height)
    return 1;
  // top right
  if (attr->x + attr->width == root_attr->width && attr->y == 0)
    return 1;
  // bottom right
  if (attr->x + attr->width == root_attr->width && attr->y + attr->height == root_attr->height)
    return 1;
  return 0;
}

int main() {
  int dx = 1;
  int dy = 1;

  Display* dpy = XOpenDisplay(0x0);
  if (!dpy)
    return 1;

  Window root = DefaultRootWindow(dpy);
  XWindowAttributes root_attr;
  XGetWindowAttributes(dpy, root, &root_attr);

  while (1) {
    XWindowAttributes attr;
    Window idc_root, idc_parent;
    Window* the_windows;
    unsigned int n_windows;

    XQueryTree(dpy, root, &idc_root, &idc_parent, &the_windows, &n_windows);

    if (n_windows > 0) {
      XWindowAttributes attr;

      XGetWindowAttributes(dpy, *the_windows, &attr);

      // change the directions if we hit an edge, depending on which edge
      if (attr.x + attr.width >= root_attr.width)
        dx = -1;
      else if (attr.x <= 0)
        dx = 1;
      if (attr.y + attr.height >= root_attr.height)
        dy = -1;
      else if (attr.y <= 0)
        dy = 1;

      XMoveResizeWindow(dpy, *the_windows,
          attr.x + dx,
          attr.y + dy,
          attr.width,
          attr.height);

      if (corners(&attr, &root_attr))
        printf("🎉🎉🎉🎉 Hit a corner!! 🎉🎉🎉🎉\n");
    }
    usleep(200000);
  }
}


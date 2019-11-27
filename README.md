# bouncywm

This nonsense was written after inspiration from https://jvns.ca/blog/2019/11/25/challenge--make-a-bouncy-window-manager/

To run it:

```
make

Xephyr -ac -screen 1280x1024 -br -reset -terminate 2> /dev/null :1 &

env DISPLAY=:1 ./bouncewm &

xterm -display :1 &
```

(These are the exact same instructions as in the link above! 😀

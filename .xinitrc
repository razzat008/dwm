#!/usr/bin/env bash
# sxhkd -c ~/.config/sxhkd/sxhkdrc &
exec slstatus &
# map caps lock button as escape button
setxkbmap -option caps:escape
#xrdb merge ~/.Xresources
#bash ~/.scripts/bash_scripts/e.sh &
nitrogen --restore --set-scaled ~/Downloads/wallpaperflare.com_wallpaper.jpg &
#exec dwmblocks &
picom -b --config=/home/ceaser/.config/picom/picom.conf &
#to update dwm without closing the running apps
while type dwm >/dev/null; do dwm && continue || break; done
# 
systemctl --user import-environment DISPLAY
#
exec dunst -config ~/.config/dunst/dunstrc &

# xautolock -time 1 -locker slock
# [ ! -s ~/.config/mpd/pid ] && mpd
# MPD daemon start (if no other user instance exists)
[ ! -s ~/.config/mpd/pid ] && mpd

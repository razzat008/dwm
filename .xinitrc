#!/usr/bin/env bash
sxhkd -c ~/.config/sxhkd/sxhkdrc &
exec slstatus &
#xrdb merge ~/.Xresources 
#bash ~/.scripts/bash_scripts/e.sh &
nitrogen --restore --set-scaled ~/Downloads/wallpaperflare.com_wallpaper.jpg &
#exec dwmblocks &
picom -b --config=/home/ceaser/.config/picom/picom.conf &
#to update dwm without closing the running apps
while type dwm >/dev/null; do dwm && continue || break; done


exec dunst -config ~/.config/dunst/dunstrc &

[ ! -s ~/.config/mpd/pid ] && mpd



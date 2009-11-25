#glc-play stream.fifo -o audio.fifo -a 1 &
glc-play stream.fifo -o - -y 1 | ffmpeg -i - -vcodec mpeg4 -f mpegts -s 720x432 -r 30 -re -b 2000k -threads 2 udp://127.0.0.1:1234

# mencoder - -demuxer y4m -nosound -ovc x264 -x264encopts qp=18:pass=1 -of avi -o udp://127.0.0.1:1234 
#glc-play stream.fifo -o video.fifo -p 1 &
#ffmpeg -i video.fifo -vcodec copy -f mpegts rtp://127.0.0.1:1234

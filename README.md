YoloCut

Tool for cutting videos from frames which don't present desired objects.
The intention was to automatically preprocess skate videos to cut out scenes without person and skateboard.
I based my implementation on the YoloV3 examples from https://github.com/spmallick/learnopencv/tree/master/ObjectDetection-YOLO.

Example:

input
https://youtu.be/tob3PN2lnsc

output
https://www.youtube.com/watch?v=UnfoIU_GHHA

cut out scenes
https://www.youtube.com/watch?v=eP5Uh_KXV5A


TODO:
- Use ffmpeg to cut video
- Move config to json
- Read args
- Train model on my own dataset
- Detect if person is on skateboard
- Speed it up

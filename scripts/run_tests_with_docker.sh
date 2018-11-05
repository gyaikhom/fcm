docker image build -t fcm:latest .
#docker container run -e CODECOV_TOKEN=$CODECOV_TOKEN  --interactive --tty --rm --name fcm fcm:latest
docker container run  --interactive --tty --rm --name fcm fcm:latest

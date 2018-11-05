FROM ahmad88me/fcm:latest

RUN mkdir -p /app
WORKDIR /app


COPY scripts /app/scripts
COPY Makefile /app/
COPY *.c /app/
COPY *.cpp /app/
COPY *.h /app/

CMD ["sh", "scripts/start.sh"]

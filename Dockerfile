FROM alpine:3.14

RUN apk add git boost meson ninja g++ cmake zlib-dev openssl-dev boost-dev curl-dev

RUN git clone https://gitlab.com/car.margiotta/pathfinder2-telegram.git --recursive
RUN	cd pathfinder2-telegram && \
	meson build && ninja -C build && \
	mv build/src/inventory_bot ../ && \
	mv build/test/inventory_test ../ && \
	cd .. && rm -r pathfinder2-telegram

ENTRYPOINT ["./inventory_bot"]
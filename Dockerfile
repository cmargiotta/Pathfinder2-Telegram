FROM alpine:3.14
RUN apk add git boost meson ninja g++ cmake zlib-dev openssl-dev boost-dev curl-dev

RUN git clone https://gitlab.com/car.margiotta/pathfinder2-telegram.git --recursive
RUN	cd pathfinder2-telegram && \
	meson build && ninja -C build
RUN mv pathfinder2-telegram/build/src/inventory_bot ./ && \
	mv pathfinder2-telegram/build/src/test/inventory_test && \
	rm -r pathfinder2-telegram

ENTRYPOINT ["./inventory_bot"]
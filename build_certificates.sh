#!/bin/sh

openssl req -newkey rsa:2048 -sha256 -nodes -keyout /usr/share/inventory_bot/certs/private.key -x509 -days 365 -out /usr/share/inventory_bot/certs/public.pem -subj ""
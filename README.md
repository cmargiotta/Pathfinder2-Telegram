# A lightweight Telegram bot for managing inventories of Pathfinder 2, perfect for self-hosted environment

### **Note**: this inventory manager is meant to handle only one master and his players.

**This project is not affiliated with Pathfinder 2e or Paizo.**

## Features

- Player:
    - Automatic occupied bulk calculation
    - Flexible search of items registered by the master
    - Custom items with name, bulk and category
    - Categorized view of the inventory
    - Full money manager, with automatic division  into cp, sp and gp 

- Master:
    - Username based authorization
    - Easy registration of new items in the database, with description (full Telegram markdown support), bulk, URL (for Wiki contents or for images), name and category,
    - Easy remotion of items from DB,
    - Possibility to edit items 

## Usage
### Configuration

The parameters are passed to the bot using runtime environment. 
The following variables must be defined:
```
PF2_INV_BOT_TOKEN=BOT TOKEN
PF2_INV_MASTER=Master username
PF2_INV_LANG=Language
```

These are optional ones:
```
PF2_INV_PORT=port
PF2_INV_DB_PATH=DB path
PF2_INV_WEBHOOK_URL=URL
```

If `PF2_INV_WEBHOOK_URL` is not defined the bot will run in active poll mode, a more resource greedy mode that does not require port forwarding and static external IP/dynamic DNS.

Other default values (when not specified):
- `PF2_INV_PORT`: 8080
- `PF2_INV_DB_PATH`: ./pf2_inv.db

### Build from source

Requirements:
- meson
- boost
- ninja
- cmake
- libssl
- libcurl

```
git clone https://gitlab.com/-/ide/project/car.margiotta/pathfinder2-telegram/ --recursive
cd pathfinder2-telegram
meson build
ninja -C build test
```

The executable will be at `build/src/pathfinder2_inv`.

To install: 

```
cd build
sudo meson install
```

This will install the executable in `/usr/bin/inventory_bot`, a `.service` file, the environment file in `/etc/inventory_bot.env` and the localized JSONs in `/usr/share/inventory_bot/localized_data/`. You will need to provide SSL certificates in `/usr/share/inventory_bot/certs/public.crt` and `/usr/share/inventory_bot/private.key`.

You can generate custom certificates with:

```
openssl req -newkey rsa:2048 -sha256 -nodes -keyout /usr/share/inventory_bot/certs/private.key -x509 -days 365 -out /usr/share/inventory_bot/certs/public.crt -subj "/C=IT/CN=$PF2_INV_WEBHOOK_URL"
```

You are free to edit `/usr/share/inventory_bot/localized_data/[messages, commands]_language.json` to customize messages and keyboards and to add new languages support.

To run the bot service: 

```
sudo systemctl start inventory_bot
```

## TODOs

- Add broadcast message (master feature)
- Add "give item to player" command (master feature)
- Add web interface for master and players 

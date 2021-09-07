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

### Docker

The easiest way to run this bot is to use the preconfigured Docker environment.

```bash
docker pull registry.gitlab.com/car.margiotta/pathfinder2-telegram
docker run pathfinder2-telegram --env-file config.env -p 8080:8080
```

With an environment defined in the file `config.env`, it will expose port 8080.

### Build from source

Requirements:
    - meson
    - boost
    - ninja

```
git clone https://gitlab.com/-/ide/project/car.margiotta/pathfinder2-telegram/
cd pathfinder2-telegram
meson build
ninja -C build test
```

The executable will be at `build/src/pathfinder2_inv`

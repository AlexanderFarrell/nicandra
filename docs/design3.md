# Nicandra Design

Nicandra's prime goal is to provide a programming interface for apps, games, and (in the future) servers. It focuses on being portable, efficient, and unified. 

- Core
- Assets
- Worlds
- UIs
- Windows
    - Input
    - Renderers
- Runtime
- Data
- Platform
    - Audio
    - Graphics
    - Peripherals
    - OS
    - Environment
    - Sync
    - Time
    - FS/Network


- Assets - Manages resources (images, sounds, configs, worlds, etc.). Can load, save, serialize/deserialize and allow generation. Can also hold handles to: files, web-resources, gpu-resources, etc. 
    - Register Asset types, get an asset_type_id. 
    - Save or load assets at specific OS locations
    - Access resources easily
    - Some resources, such as textures, can have GPU handles as well. Or audio with sound handle. 
    - Also provides database access?

- Worlds
    - Common runtime environment which provides nouns, components, and verbs. Used for game worlds, and UI. 

- Core - Entry-point and primary runtime for the selected app. Provides lifecycle of the app, and initialization. 

- 
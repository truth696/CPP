# 🎬 YouTube-like Platform (C++)

A small C++ project that models a **YouTube-style platform**: platform, channels, users, and different video types (shorts, regular, live streams) with creators and notifications.

---

## 📁 Project tree

```
CPP_JANUARY_23_YouTube/
├── 📄 Makefile
├── 📄 README.md
├── 📂 include/
│   ├── Channels.hpp       🎯 Channel, subscribers, videos
│   ├── LiveStream.hpp     📡 Live stream video
│   ├── LiveStreamCreator.hpp
│   ├── RegularVideo.hpp    🎞️ Regular video
│   ├── RegularVideoCreator.hpp
│   ├── ShortVideo.hpp     ⏱️ Short video
│   ├── ShortVideoCreator.hpp
│   ├── User.hpp           👤 Subscriber
│   ├── Video.hpp          🎥 Base video
│   ├── VideoCreator.hpp   🏭 Creator base
│   └── YouTube.hpp        🏠 Platform root
└── 📂 src/
    ├── Channels.cpp
    ├── LiveStreamCreator.cpp
    ├── main.cpp           ✅ Functionality check
    ├── RegularVideoCreator.cpp
    ├── ShortVideoCreator.cpp
    ├── User.cpp
    └── YouTube.cpp
```

---

## ✨ Functionality (short)

| Area | What it does |
|------|------------------|
| 🏠 **Platform** | Create platform, add/remove channels by name |
| 🎯 **Channels** | Subscribe/unsubscribe users, add/delete videos, notify subscribers |
| 👤 **Users** | Subscribe to channels, get notified when new content is posted |
| 🎥 **Videos** | Short / Regular / LiveStream; created via Creator classes |
| 🏭 **Creators** | Factory-style creation of each video type |

Run the binary to run the built-in **functionality check** and see **ALL RIGHT** or which checks failed.

---

## 📊 Advantages vs issues to avoid

| ✅ Advantages | ⚠️ Issues to avoid |
|---------------|---------------------|
| 🧩 Clear separation: Platform → Channels → Users, Videos | 🔗 **Circular includes** — use forward declarations (e.g. `User`, Creator classes) |
| 🔄 Observer-like flow: new video → notify subscribers | 🔁 **shared_ptr cycles** (Channel ↔ User) — break before destroy or use weak_ptr on one side |
| 🏭 Creator pattern for video types (extensible) | 📤 **Return by reference** from creators — prefer `shared_ptr<Video>` to avoid lifetime bugs |
| 🎯 Polymorphism: `Video` base, Short/Regular/LiveStream | 🐛 **Loop conditions** — use `i < vec.size()` not `vec.size()` in for-loops |
| 🛡️ `enable_shared_from_this<User>` for safe subscribe | 📢 **Use-after-move** — in `addVideo`, use `v->getType()` before `std::move(v)` |
| 🎬 Virtual destructor on `Video` for safe delete via base pointer | 🧪 **Video tests** — if getType/crash on base pointer, see “Known issues” below |

---

## 🧩 Design patterns used

| Pattern | Where | Role |
|--------|--------|------|
| **Singleton-like** | `YouTube::getRoot()` / `CreatePlatform()` | Single platform instance |
| **Factory / Creator** | `CreatorShortVideo`, `CreatorRegularVideo`, `CreatorLiveStream` | Create concrete video types without exposing constructors |
| **Observer (light)** | Channel → `notify_subscribers()` when a video is added | Users get “new content” notifications |
| **Template Method (style)** | `Video` base + virtual `getType()` / `getDescription()` | Same interface for all video kinds |
| **Shared ownership** | `shared_ptr<Channel>`, `shared_ptr<User>`, `shared_ptr<Video>` | Clear ownership and lifetime between entities |

---

## 🚀 Build & run

```bash
make        # build → produces `ems`
./ems       # run functionality check
make clean  # remove object files and binary
```

---

## 📌 Known issues / notes

- **Video tests (4–6)** are skipped in the automated check to avoid crashes (e.g. when calling `getType()` through a base pointer on creator-returned objects). Platform, channels, and subscribe/notify are fully exercised.
- **Creators** return a reference to heap-allocated video; wrapping in `shared_ptr` and avoiding use-after-move in `addVideo` is important for correct behavior.

---

*Small educational project — platform, channels, users, and video types in C++.*

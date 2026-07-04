# zcol

Single-header C++23 colored terminal output & logging library.

## Project Structure

- `zcol.hpp` — the single header, the only deliverable
- `CMakeLists.txt` — header-only INTERFACE library, requires CMake 4.0+ and C++23
- `.github/workflows/` — CI and release automation

## CI / CD Rules

### Build (cmake-multi-platform.yml)

- Triggers on push/PR to `main`
- Matrix: ubuntu (gcc, clang) + windows (msvc)
- Uses `actions/checkout@v5` (v4 uses deprecated Node.js 20)
- Uses `lukka/get-cmake@latest` to install CMake 4.x (project requires 4.0+)
- Build only — no test step (no test suite yet)

### Release (release.yml)

- Triggers on tag push matching `v*`
- Uses `softprops/action-gh-release@v2`
- Attaches `zcol.hpp` to the release
- Auto-generates release notes

## Release Flow

```bash
git tag v1.0.0
git push origin v1.0.0
```

This automatically creates a GitHub Release with the header file attached.

## Rules

- Never downgrade `actions/checkout` below v5
- Never downgrade CMake minimum version below 4.0
- Single-header library — only `zcol.hpp` should be in the release artifact

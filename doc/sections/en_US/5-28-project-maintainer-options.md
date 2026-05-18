## Project maintainer options

The packager targets that bake the maintainer identity into the produced artefact (DEB, RPM, FreeBSD pkg, WIX MSI) read it from a shared pair of Meson options:

| Option | Default | Used by |
|---|---|---|
| `-DPROJECT_MAINTAINER='Your Name'` | `Your Name` | `deb`, `rpm`, `freebsd-pkg`, `wix` |
| `-DPROJECT_MAINTAINER_EMAIL='you@example.com'` | `yourname@your.email.org` | `deb`, `rpm`, `freebsd-pkg` |

These can be combined with any of the enable-flags described in the per-packager subsections. For example:

```
meson setup build -DENABLE_DEB=true \
  -DPROJECT_MAINTAINER='Your Name' \
  -DPROJECT_MAINTAINER_EMAIL='you@example.com'
meson compile -C build deb
```

Leaving these options at their defaults will produce a working package, but the resulting metadata will not identify your project correctly - set them before publishing artefacts.

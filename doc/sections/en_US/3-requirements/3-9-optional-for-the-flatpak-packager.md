## Optional for the flatpak packager

In order to generate the project flatpak package install the `flatpak-builder` command:

```
sudo apt install -y flatpak flatpak-builder
```

You'll also need the one of it's target SDK which may be installed by a command that may look like this:

```
flatpak install --user flathub runtime/org.gnome.Platform/x86_64/49 runtime/org.gnome.Sdk/x86_64/49
```

The `49` is the `runtime-version` the [misc/packagers/flatpak/flatpak.conf.json.in](/misc/packagers/flatpak/flatpak.conf.json.in) manifest builds against: change both together to use another runtime. Consult the flatpak documentation on how to list all available options.

The `flatpak` target installs the runtime and the SDK it needs from the `flathub` remote on its own, so the command above only preinstalls them.

Look for the details at the [Enabling the flatpak package generation support](/doc/sections/en_US/5-project-build/packagers/5-11-enabling-the-flatpak-package-generation-support.md).

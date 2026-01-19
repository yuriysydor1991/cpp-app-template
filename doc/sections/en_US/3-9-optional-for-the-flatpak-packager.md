## Optional for the flatpak packager

In order to generate the project flatpak package install the `flatpak-builder` command:

```
sudo apt install -y flatpak flatpak-builder
```

You'll also need the one of it's target SDK which may be installed by a command that may look like this:

```
flatpak install runtime/org.kde.Sdk/x86_64/6.8
flatpak install runtime/org.kde.Platform/x86_64/6.8
```

Replace the `runtime/org.kde.Sdk/x86_64/6.8` and `runtime/org.kde.Platform/x86_64/6.8` with your preferred SDK. Consult the flatpak documentation on how to list all available options.

Look for the details at the [Enabling the flatpak package generation support](/doc/sections/en_US/5-11-enabling-the-flatpak-package-generation-support.md).

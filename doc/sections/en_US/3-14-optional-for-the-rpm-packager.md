## Optional for the rpm packager

In order to generate the project RPM package install the `rpmbuild` command. On Fedora/RHEL/openSUSE based hosts:

```
# Fedora / RHEL
sudo dnf install -y rpm-build

# openSUSE
sudo zypper install -y rpm-build
```

On Debian/Ubuntu hosts a `rpmbuild` is shipped through the `rpm` package:

```
sudo apt install -y rpm
```

Look for the details at the [Enabling the RPM package generation support](/doc/sections/en_US/5-24-enabling-rpm-package-generation.md) section.

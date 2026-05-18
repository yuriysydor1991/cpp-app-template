## Необов'язкові пакети для пакувальника rpm

Для того щоб генерувати RPM-пакет проекту необхідно встановити команду `rpmbuild`. Для Fedora/RHEL/openSUSE дистрибутивів:

```
# Fedora / RHEL
sudo dnf install -y rpm-build

# openSUSE
sudo zypper install -y rpm-build
```

На Debian/Ubuntu системах `rpmbuild` доступний через пакет `rpm`:

```
sudo apt install -y rpm
```

Деталі у секції [Вмикання підтримки генерації RPM-пакету](/doc/sections/uk_UA/5-24-enabling-rpm-package-generation.md).

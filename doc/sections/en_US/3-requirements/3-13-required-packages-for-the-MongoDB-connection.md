## Required packages for the MongoDB connection

In order to make the MongoDB C driver, which the C++ one of the template project builds upon, available install it with a next command (GNU/Linux based OS):

```
sudo apt install -y libmongoc-dev libbson-dev
```

The archives of the most of the distributions carry no MongoDB C++ driver package at all, so the [mongocxx enabler](/doc/sections/en_US/5-project-build/5-38-enabling-the-mongocxx-library.md) fetches and builds that driver itself when the system carries none. The C driver packages above are the optional ones which spare the fetched sources that part of the build.

### Connecting to the MongoDB server

The executable connects to the [MongoDB](https://www.mongodb.com/) server at the `localhost:27017` address with no credentials by default. The distribution archives carry no MongoDB server package, so install it from the [MongoDB Community Edition](https://www.mongodb.com/docs/manual/administration/install-community/) repositories or start the official container image, for example:

```
docker run --rm -d -p 27017:27017 --name mongodb mongo
```

The connection settings are taken from the next environment variables, when set:

- `MONGODB_HOST` - the server host name (`localhost` by default);
- `MONGODB_PORT` - the server port (`27017` by default);
- `MONGODB_USER` - the user name; the credentials part of the connection string is added only when it is set;
- `MONGODB_PASSWORD` - the user password;
- `MONGODB_DATABASE` - the database the user is authenticated against;
- `MONGODB_TLS` - the `true` or the `false` value to turn the TLS on or off; when unset the TLS is used for the connections with credentials only;
- `MONGODB_TIMEOUT_MS` - the server selection and connect timeout in milliseconds (`5000` by default).

The driver connects lazily, so the executable pings the server right after the connection creation, and an unreachable server fails the start within the `MONGODB_TIMEOUT_MS` time instead of the 30 seconds of the driver default server selection timeout.

The user name, the password and the database name are percent-encoded, so any characters may be used in them. To create a user for the template on the server execute a next command:

```
mongosh --eval 'db.getSiblingDB("templatedb").createUser({user: "template_user", pwd: "template_password", roles: [{role: "readWrite", db: "templatedb"}]})'
```

and start the executable with the matching settings:

```
MONGODB_USER=template_user MONGODB_PASSWORD=template_password MONGODB_DATABASE=templatedb ./CppAppTemplate
```

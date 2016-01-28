# Example: Defining Permissions #
In order to execute an action you need to allow a certain type of user to execute that action. In the buildacl.inc file there are 3 roles by default - guest, user, admin - and the index action.
To allow a guest to view our new action add the following lines:
```
$acl->addAction('hello', 'world');
$acl->authorize('guest', 'hello', 'world');
```
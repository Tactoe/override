import os
import sys

def main():
    print ("***********************************")
    print ("* \t     -Level00 -\t\t  *")
    print ("***********************************")
    password = input("Password:")
    if (int(password) == 5267):
        # get the effective group id and user id of the binary (in this case, the admin)
        gid = os.getegid() 
        uid = os.geteuid()
        # override the current user / group id with those values and run a shell
        os.setresgid(gid)
        os.setresuid(uid)
        # execv expects a single list of arguments (the first of which should be the name of the executable)
        os.execv("/bin/sh", ["/bin/sh"])
    else:
        print("\nInvalid Password!")

if __name__ == '__main__':
    main()
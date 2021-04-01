#Color Printing for python2.7
# This is a script that implements a function used to print colored text
# Note: If this causes problems, you can remove it
# but to do this you also need to edit all calls to
# pretty or prettyln in plain print  
#it will not automaticlly jump to new line so remember to use \n
def pretty(string,color) :
    if (color == "r") :
        print '\033[31m',
        print string,
        print '\033[0m'  
    elif (color == "g") :
        print '\033[32m',
        print string,
        print '\033[0m', 
    else :
        print "Invalid option: "+color

def prettyln(string,color):
    if (color == "r") :
        print '\033[31m'
        print string,
        print '\033[0m',  
    elif (color == "g") :
        print '\033[32m'
        print string,
        print '\033[0m',
    else :
        print "Invalid option: "+color

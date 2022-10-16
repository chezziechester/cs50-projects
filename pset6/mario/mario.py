from cs50 import get_int

# recursively draw the layers


def drawLayer(layer, height):
    # base case to check if it has hit 0
    if layer == 0:
        return
    # when base case returns, starts going through the stack (starting from highest layer)
    drawLayer(layer - 1, height)
    # no separators
    print(" " * (height - layer), "#" * layer, " " * 2, "#" * layer, sep='')
    
    
def main():
    # input value must be between 1 and 8
    while True:
        height = get_int("Height: ")
        if height <= 8 and height >= 1:
            break
        
    drawLayer(height, height)
 

main()
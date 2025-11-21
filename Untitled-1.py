#!/usr/bin/env python3
from turtle import *

class Disc(Turtle):
    def __init__(self, n):
        Turtle.__init__(self, shape="square", visible=False)
        self.pu()
        self.shapesize(1.5, n*1.5, 2)
        self.fillcolor(n/6., 0, 1-n/6.)
        self.st()

class Tower(list):
    def __init__(self, x):
        self.x = x
        
    def push(self, d):
        d.setx(self.x)
        d.sety(-150+34*len(self))
        self.append(d)
        
    def pop(self):
        d = list.pop(self)
        d.sety(150)
        return d

def hanoi(n, from_, with_, to_, step_counter=[0]):
    """增强版汉诺塔函数，显示递归步骤"""
    if n > 0:
        # 步骤1：递归移动n-1个盘子
        print(f"步骤{step_counter[0]}: 将 {n-1} 个盘子从 {from_.x} 经过 {to_.x} 移动到 {with_.x}")
        hanoi(n-1, from_, to_, with_, step_counter)
        
        # 步骤2：移动最大的盘子
        step_counter[0] += 1
        print(f"步骤{step_counter[0]}: 移动盘子 {n} 从 {from_.x} 到 {to_.x}")
        to_.push(from_.pop())
        
        # 步骤3：递归移动n-1个盘子
        print(f"步骤{step_counter[0]}: 将 {n-1} 个盘子从 {with_.x} 经过 {from_.x} 移动到 {to_.x}")
        hanoi(n-1, with_, from_, to_, step_counter)

def play():
    onkey(None,"space")
    clear()
    try:
        # 重置步骤计数器
        step_counter = [0]
        hanoi(3, t1, t2, t3, step_counter)  # 先用3个盘子演示
        write("完成！共{}步".format(step_counter[0]),
              align="center", font=("Courier", 16, "bold"))
    except Terminator:
        pass

def main():
    global t1, t2, t3
    ht(); penup(); goto(0, -225)
    t1 = Tower(-250)
    t2 = Tower(0)
    t3 = Tower(250)
    
    # 创建3个盘子（为了演示清晰）
    for i in range(3,0,-1):
        t1.push(Disc(i))
        
    write("按空格键开始递归演示（3个盘子）",
          align="center", font=("Courier", 14, "bold"))
    onkey(play, "space")
    listen()
    return "EVENTLOOP"

if __name__=="__main__":
    msg = main()
    print(msg)
    mainloop()
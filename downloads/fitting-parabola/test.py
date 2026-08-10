import numpy as np
import matplotlib.pyplot as plt


# set figure
fig = plt.figure()
ax = fig.gca(projection='3d')

################################################## input args #############################################
# startPos and endPos in [lon, lat, height]
stPos = [117.9844565, 24.1658956, 1.597]
edPos = [118.1167438, 24.5656241, 5211.73]

# # stTime, endTime, in seconds, assume it take 1 minute for missile from emit to explode
# stTime = 0
# endTime = 10

# step number
stepNumber = 30
################################################## input args #############################################

################################################## output     #############################################
# res
resX = []
resY = []
resZ = []
################################################## output     #############################################

# land defend air means, should satisfy: st.z < ed.z
# (z-z1)**2 = p*(x-x1)
def computeLnadDefendAirParabolaWithSteps(
    st, 
    ed, 
    resX, 
    resY, 
    resZ, 
    stepNum
    ):
    resX.append(st[0])
    resY.append(st[1])
    resZ.append(st[2])

    p = (ed[2] - st[2])**2 / (ed[0] - st[0])
    step = (ed[0] - st[0]) / stepNum
    for stepCnt in range(stepNum)[1:]:
        curX = st[0] + stepCnt * step
        curZ = (p * (curX - st[0])) ** 0.5 + st[2]
        resZ.append(curZ)
        # compute projection from x to y: x = k*y + b
        if st[1] != ed[1]:
            k = (st[0] - ed[0]) / (st[1] - ed[1])
            b = st[0] - k * st[1]
            curY = (curX - b) / k
            resY.append(curY)
            resX.append(curX)
        else:
            # all the y is the same
            resY.append(curY)
            resX.append(curX)
    resX.append(ed[0])
    resY.append(ed[1])
    resZ.append(ed[2])

    # print
    for idx in range(stepNum + 1):
        print("%10.6f, %10.6f, %10.3f"%(resX[idx], resY[idx], resZ[idx]))


computeLnadDefendAirParabolaWithSteps(stPos, edPos, resX, resY, resZ, stepNumber)

# 绘制图形
ax.plot(resX, resY, resZ, label='fitted curve')

# 显示图例
ax.legend()

# 显示图形
plt.show()
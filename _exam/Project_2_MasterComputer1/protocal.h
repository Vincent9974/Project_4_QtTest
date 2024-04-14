#ifndef PROTACAL_H
#define PROTACAL_H

const char tempQuery = 0x01; //主机温度查询命令
const char tempResponse = 0x02; //主机温度响应命令

const char workingShaftRPMQuery = 0x03; //工作轴转速查询命令
const char workingShaftRPMResponse = 0x04; //工作轴转速响应命令

const char tankPressureQuery = 0x05; //压力仓压力查询命令
const char tankPressureResponse = 0x06; //压力仓压力响应命令

const char fuelQuery = 0x07; //工作缸油量查询命令
const char fuelResponse = 0x08; //工作缸油量响应命令

const char armPressureQuery = 0x09; //机械臂压力查询命令
const char armPressureResponse = 0x0A; //机械臂压力响应命令

const char powerRodSpeedQuery = 0x0B; //动力杆速度查询命令
const char powerRodSpeedResponse = 0x0C; //动力杆速度转速响应命令

#endif // PROTACAL_H

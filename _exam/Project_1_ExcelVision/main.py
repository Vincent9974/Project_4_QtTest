# import pytesseract
# from PIL import Image


# testdata_dir_config = '--tessdata-dir "C:\\Program Files (x86)\\Tesseract-OCR\\tessdata"'

# text_ch = pytesseract.image_to_string(Image.open('./image/1.png'), config=testdata_dir_config, lang='chi_sim').replace('\n', '')
# text_eng = pytesseract.image_to_string(Image.open('./image/1.png'), config=testdata_dir_config, lang='eng').replace('\n', '')

# # 合并识别结果
# merged_text = text_ch + '\n' + text_eng
# print(merged_text)

# import cv2
# import pytesseract

# testdata_dir_config = '--tessdata-dir "C:\\Program Files (x86)\\Tesseract-OCR\\tessdata"'

# # 读取图片
# image = cv2.imread('./image/1.png')

# # 将图片转换为灰度图像
# gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)

# # 使用二值化将图像转换为黑白图像
# _, binary = cv2.threshold(gray, 0, 255, cv2.THRESH_BINARY_INV + cv2.THRESH_OTSU)

# # 查找图像中的轮廓
# contours, _ = cv2.findContours(binary, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)

# my_list = []

# # 遍历轮廓
# for contour in contours:
#     # 获取轮廓的边界框
#     x, y, w, h = cv2.boundingRect(contour)
    
#     # 提取数字区域
#     digit_region = image[y:y+h, x:x+w]
    
#     # 使用 pytesseract 进行数字识别
#     digit_text = pytesseract.image_to_string(digit_region,config=testdata_dir_config,lang='eng').replace('\n', '')

#     my_list.append(digit_text)
    
#     # # 在原始图像上绘制识别结果
#     # cv2.rectangle(image, (x, y), (x + w, y + h), (0, 255, 0), 2)
#     # cv2.putText(image, digit_text, (x, y - 10), cv2.FONT_HERSHEY_SIMPLEX, 0.7, (0, 0, 255), 2)

# # # 显示结果图像
# # cv2.imshow("Output", image)
# # cv2.waitKey(0)
# # cv2.destroyAllWindows()

# # for x in my_list:
# #     print(x)

# print(my_list)

# import cv2
# import pytesseract
# import re

# testdata_dir_config = '--tessdata-dir "C:\\Program Files (x86)\\Tesseract-OCR\\tessdata"'

# # 读取图片
# image = cv2.imread('./image/1.png')

# # 将图像转换为灰度图像
# gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)

# # 使用二值化将图像转换为黑白图像
# _, binary = cv2.threshold(gray, 0, 255, cv2.THRESH_BINARY_INV + cv2.THRESH_OTSU)

# # 查找图像中的轮廓
# contours, _ = cv2.findContours(binary, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)

# # # 查找图像中的轮廓
# # contours, _ = cv2.findContours(binary, cv2.RETR_LIST, cv2.CHAIN_APPROX_SIMPLE)


# my_list_en = []
# my_list_ch = []

# # 遍历轮廓
# for contour in contours:
#     # 获取轮廓的边界框
#     x, y, w, h = cv2.boundingRect(contour)
    
#     # 提取数字区域
#     digit_region = image[y:y+h, x:x+w]
    
#     # 使用 pytesseract 进行数字识别
#     digit_text_en = pytesseract.image_to_string(digit_region,config=testdata_dir_config,lang='eng').replace('\n', '')
#     digit_text_ch = pytesseract.image_to_string(digit_region,config=testdata_dir_config,lang='chi_sim').replace('\n', '')

#     # 如果识别结果不为空，则将其添加到列表中
#     if digit_text_en.strip():
#         my_list_en.append(digit_text_en.strip())

#     if digit_text_ch.strip():
#         my_list_ch.append(digit_text_ch.strip())

#     # 将每一行的识别结果打印出来
#     #print(digit_text.strip())

# # 打印列表中的识别结果
# print("List of recognized lines:", my_list_en)
# print("List of recognized lines:", my_list_ch)


# # 提取中文字符的正则表达式
# chinese_pattern = re.compile('[\u4e00-\u9fa5]')
# # 提取中文字符
# chinese_characters = []
# for text in my_list_ch:
#     chinese_characters.extend(chinese_pattern.findall(text))


# import cv2
# import pytesseract
# import re

# # 设置 Tesseract OCR 的配置
# testdata_dir_config = '--tessdata-dir "C:\\Program Files (x86)\\Tesseract-OCR\\tessdata"'

# # 读取图片
# image = cv2.imread('./image/1.png')

# # 将图像转换为灰度图像
# gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)

# # 使用二值化将图像转换为黑白图像
# _, binary = cv2.threshold(gray, 0, 255, cv2.THRESH_BINARY_INV + cv2.THRESH_OTSU)

# # 查找图像中的轮廓
# contours, _ = cv2.findContours(binary, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)

# # 将数字区域按行分组
# digit_regions = []

# # 遍历轮廓
# for contour in contours:
#     # 获取轮廓的边界框
#     x, y, w, h = cv2.boundingRect(contour)
    
#     # 提取数字区域
#     digit_region = image[y:y+h, x:x+w]
    
#     # 将数字区域添加到列表中
#     digit_regions.append((x, y, digit_region))

# # 按照轮廓左上角的 y 坐标进行排序
# digit_regions.sort(key=lambda x: x[1])

# # 识别结果列表
# recognized_text = []

# # 遍历数字区域
# for x, y, digit_region in digit_regions:
#     # 使用 pytesseract 进行数字识别
#     text = pytesseract.image_to_string(digit_region, config=testdata_dir_config)
    
#     # 如果识别结果不为空，则将其添加到列表中
#     if text.strip():
#         recognized_text.append(text.strip())

# # 分离连续的中文字符和英文数字
# chinese_pattern = re.compile('[\u4e00-\u9fa5]')
# english_number_pattern = re.compile('[a-zA-Z0-9]+')
# separated_text = []
# for text in recognized_text:
#     chinese_texts = chinese_pattern.findall(text)
#     english_number_texts = english_number_pattern.findall(text)
#     separated_text.extend(chinese_texts)
#     separated_text.extend(english_number_texts)

# # 打印分割后的文本
# print("Separated text:", separated_text)


import cv2
import pytesseract
import re
import mysql.connector
import os

# 添加最新的路径

# 文件夹路径
folder_path = 'F:\\UserData\\Documents\\GitHubRepo\\PythonTest\\ExcelVision\\image'

# 获取文件夹中的所有文件
files = os.listdir(folder_path)

# 排序文件列表，根据文件的修改时间进行降序排序
files.sort(key=lambda x: os.path.getmtime(os.path.join(folder_path, x)), reverse=True)

# 获取最新添加的文件路径
newest_file_path = os.path.join(folder_path, files[0])

newest_file_path = newest_file_path.replace('\\', '/')

filePath = newest_file_path

# filePath = './image/1.png'

# 设置 Tesseract OCR 的配置
testdata_dir_config = '--tessdata-dir "C:\\Program Files (x86)\\Tesseract-OCR\\tessdata"'

# 读取图片
image = cv2.imread(filePath)

# 将图像转换为灰度图像
gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)

# 使用二值化将图像转换为黑白图像
_, binary = cv2.threshold(gray, 0, 255, cv2.THRESH_BINARY_INV + cv2.THRESH_OTSU)

# 查找图像中的轮廓
contours, _ = cv2.findContours(binary, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)

# 将数字区域按行分组
digit_regions = []

# 遍历轮廓
for contour in contours:
    # 获取轮廓的边界框
    x, y, w, h = cv2.boundingRect(contour)
    
    # 提取数字区域
    digit_region = image[y:y+h, x:x+w]
    
    # 将数字区域添加到列表中
    digit_regions.append((x, y, digit_region))

# 按照轮廓左上角的 y 坐标进行排序
digit_regions.sort(key=lambda x: x[1])

# 识别结果列表
recognized_text_en = []
recognized_text_ch = []

# 遍历数字区域
for x, y, digit_region in digit_regions:
    # 使用 pytesseract 进行数字识别
    text_en = pytesseract.image_to_string(digit_region, config=testdata_dir_config, lang='eng')
    text_ch = pytesseract.image_to_string(digit_region, config=testdata_dir_config, lang='chi_sim')
    
    # 如果识别结果不为空，则将其添加到列表中
    if text_en.strip():
        recognized_text_en.append(text_en.strip())
    if text_ch.strip():
        recognized_text_ch.append(text_ch.strip())


# 合并连续的数字区域标点符号
merged_text_en = []
for text in recognized_text_en:
    # 如果文本中包含数字和标点符号，则合并它们
    if re.search(r'[0-9]+[.,]?[0-9]*', text):
        merged_text_en.append(re.sub(r'(\d+)[.,]?(\d*)', r'\1\2', text))
    else:
        merged_text_en.append(text)

# 打印合并后的文本
print("Merged text_en:", merged_text_en)

print("Merged text_ch:", recognized_text_ch)


# 创建一个新的列表来存放日期
dates = []

# 正则表达式模式用于匹配日期
date_pattern = r'\d{4}-\d{2}-\d{2}'

# 遍历原始文本列表
for text in merged_text_en:
    # 使用正则表达式在文本中查找日期
    matches = re.findall(date_pattern, text)
    
    # 将匹配到的日期添加到日期列表中
    dates.extend(matches)

# 打印日期列表
print("Dates:", dates)


# 创建一个新的列表来存放日期后面的数字
numbers_after_dates = []

# 正则表达式模式用于匹配日期后的数字
pattern = r'\d{4}-\d{2}-\d{2}\s*\n+([\d,]+)'

# 遍历 Merged text_en 列表
for text in merged_text_en:
    # 使用正则表达式在文本中查找日期后的数字
    matches = re.findall(pattern, text)
    
    # 将匹配到的数字添加到列表中
    numbers_after_dates.extend(matches)

# 打印日期后的数字列表
print("Numbers after dates:", numbers_after_dates)



# 创建一个新的列表来存放格式化后的百分比数字
formatted_percentage_numbers = []

# 正则表达式模式用于匹配以百分号结尾的数字（包含百分号）
pattern = r'(\d+(?:,\d+)?)%'

# 遍历 Merged text_en 列表
for text in merged_text_en:
    # 使用正则表达式在文本中查找以百分号结尾的数字
    matches = re.findall(pattern, text)
    
    # 格式化每个匹配到的百分比数字
    for match in matches:
        if len(match) == 2:
            formatted_percentage_numbers.append(match[0] + '.' + match[1] + '%')
        elif len(match) == 3:
            formatted_percentage_numbers.append(match[0] + match[1] + '.' + match[2] + '%')

# 打印格式化后的百分比数字列表
print("Formatted percentage numbers:", formatted_percentage_numbers)


# 创建一个新的列表来存放提取和处理后的字符串
processed_strings = []

# 遍历 Merged text_ch 列表
for text in recognized_text_ch:
    # 使用正则表达式在文本中查找符合条件的字符串
    matches = re.findall(r'\n(.*?)公.*?司', text)
    
    # 遍历匹配到的字符串
    for match in matches:
        # 去除字符串中的空格并添加到新的列表中
        processed_string = match.replace(' ', '')+ '公司'
        processed_strings.append(processed_string)

# 打印处理后的字符串列表
print("Processed strings:", processed_strings)


connection = mysql.connector.connect(
    host='localhost',
    user='root',
    password='123456',
    database='excelpicture'
)

if connection.is_connected():
    print("Connected to MySQL database")

# dates
# numbers_after_dates
# formatted_percentage_numbers
# formatted_percentage_numbers

cursor = connection.cursor()

# 插入数据
insert_query = "INSERT INTO table1 (`日期`, `金额`, `利率`, `乙方`) VALUES (%s, %s, %s, %s)"

for i in range(len(dates)):
    data = (dates[i], numbers_after_dates[i], formatted_percentage_numbers[i], processed_strings[i])
    cursor.execute(insert_query, data)

# 提交事务
connection.commit()

# 关闭游标和连接
cursor.close()
connection.close()

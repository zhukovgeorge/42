"""Tester."""


from give_bmi import give_bmi, apply_limit

height = [1.71, 1.65]
weight = [65.3, 58.4]

bmi = give_bmi(height, weight)
print(bmi, type(bmi))
print(apply_limit(bmi, 26))

bmi = give_bmi([180, 170, 12], [70, 80, 12])
bmi = give_bmi([180, "a"], [70, 80])
bmi = give_bmi([0, 0], [0, 0])

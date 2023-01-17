# define the Coleman-Liau index formula
def coleman_liau_index(num_letters, num_words, num_sentences):
    L = num_letters / num_words * 100
    S = num_sentences / num_words * 100
    index = round(0.0588 * L - 0.296 * S - 15.8)
    return index


# ask the user for some text to grade
text = input('Enter some text to grade: ')

# count the number of letters, words, and sentences in the text
num_letters = sum(c.isalpha() for c in text)
num_words = text.count(" ") + 1
num_sentences = len([c for c in text if c in '.?!'])

# calculate the Coleman-Liau index for the text
index = coleman_liau_index(num_letters, num_words, num_sentences)

# print the grade for the text
if index >= 16:
    print('Grade 16+')
elif index < 1:
    print('Before Grade 1')
else:
    print('Grade', int(index))
    
const computerChoiceDisplay = document.getElementById('computer-choice-image');
const userChoiceDisplay = document.getElementById('user-choice-image');
const resultDisplay = document.getElementById('result');
const possibleChoices = document.querySelectorAll('.choice-button');
const choices = [
    { name: 'rock', image: 'src/rock.png' },
    { name: 'paper', image: 'src/paper.png' },
    { name: 'scissors', image: 'src/scissor.png' }
];
const scoreDisplay = document.getElementById('score');
let userScore = 0;
let computerScore = 0;

possibleChoices.forEach(choice => {
    choice.addEventListener('click', handleClick);
});

function handleClick(e) {
    const userChoice = choices.find(choice => choice.name === e.target.parentNode.id);
    console.log(e.target.id);
    userChoiceDisplay.src = userChoice.image;
    const computerChoice = generateComputerChoice();
    computerChoiceDisplay.src = computerChoice.image;
    const roundResult = playRound(userChoice, computerChoice);
    resultDisplay.textContent = roundResult;
    scoreDisplay.textContent = `You: ${userScore} Me: ${computerScore}`;
}

function generateComputerChoice() {
    const randomNumber = Math.floor(Math.random() * choices.length);
    return choices[randomNumber];
}

function playRound(userChoice, computerChoice) {
    if (userChoice.name === computerChoice.name) {
        return 'Draw';
    } else if (
        (userChoice.name === 'rock' && computerChoice.name === 'scissors') ||
        (userChoice.name === 'paper' && computerChoice.name === 'rock') ||
        (userChoice.name === 'scissors' && computerChoice.name === 'paper')
    ) {
        userScore++;
        return 'You win!';
    } else {
        computerScore++;
        return 'I win!';
    }
}
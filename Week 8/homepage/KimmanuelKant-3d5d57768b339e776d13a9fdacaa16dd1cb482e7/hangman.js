// Grab the word list from the API
const wordDB = "https://random-word-api.herokuapp.com/word?number=10";

fetch(wordDB)
  .then((response) => response.json())
  .then((data) => {
    const cells = [
      "------",
      "|    o ",
      "|   /*\\",
      "|    ^ ",
      "|   / \\  ",
      "|        ",
      "/|||====|||\\"
    ];
    //console.log(data);

    const wordList = data; 
    let word;
    let correctGuesses = [];
    let incorrectGuesses = [];

    // Get the element from the HTML:
    

    // Randomly select a word from the word list
    word = wordList[Math.floor(Math.random() * wordList.length)];
    // Get the form element from the HTML
    const guessForm = document.getElementById("guess-form");
    guessForm.addEventListener("submit", function (event) {
      // Prevent the form from submitting and refreshing the page
      event.preventDefault();
      // Get the value of the input field
      let guessRaw = document.getElementById("guess-input").value;
      let guess = guessRaw.toLowerCase();
      // Check if the guess has already been submitted
      if (incorrectGuesses.includes(guess) || correctGuesses.includes(guess)) {
        // If it has, show an error message
        document.getElementById("error").textContent =
          "You've already guessed that letter. Try again.";
      } else if (word.includes(guess)) {
        // If the word includes the guess, add the guess to the correct guesses array
        correctGuesses.push(guess);
        // Update the word on the page
        updateWord();
      } else {
        // If the word does not include the guess, add the guess to the incorrect guesses array
        incorrectGuesses.push(guess);
        // Update the incorrect guesses on the page
        updateIncorrectGuesses();
        // Update the number of remaining incorrect guesses on the page
        updateRemainingGuesses();
      }
      // Clear the input field
      document.getElementById("guess-input").value = "";
    });
    // Add a listener for the restart button's click event
    document
      .getElementById("restart-button")
      .addEventListener("click", restartGame);

    // Function to update the word on the page
    function updateWord() {
      // Get the word element from the HTML
      let wordElement = document.getElementById("word");
      // Create a string to show the word with underscores and correct guesses
      let wordToShow = "";
      for (let i = 0; i < word.length; i++) {
        if (correctGuesses.includes(word[i])) {
          wordToShow += word[i] + " ";
        } else {
          wordToShow += "_ ";
        }
      }
      // Update the text content of the word element
      wordElement.textContent = wordToShow;
      // Check if the player has won the game
      checkForWin(wordToShow);
    }

    // Function to update the incorrect guesses on the page
    function updateIncorrectGuesses() {
      // Get the incorrect guesses element from the HTML
      let incorrectGuessesElement = document.getElementById("incorrect-guesses");
      // Update the text content of the element with the incorrect guesses array
      incorrectGuessesElement.textContent =
        "Incorrect Guesses: " + incorrectGuesses.join(", ");
      // Check if the player has lost the game
      checkForLoss();
    }

    // Function to update the remaining guesses on the page
    function updateRemainingGuesses() {
      let remainingGuesses = document.getElementById("remaining-guesses");
      remainingGuesses.textContent =
        "Remaining Incorrect Guesses: " + (6 - incorrectGuesses.length);
    }

    // Function to check if the player has won the game
    function checkForWin(wordToShow) {
      if (!wordToShow.includes("_")) {
        console.log("Congratulations! You won the game!");
        alert("Impressive! You found the word " + word + "!");
        restartGame();
      }
    }

    // Function to check if the player has lost the game
    function checkForLoss() {
      if (incorrectGuesses.length >= 6) {
        console.log("Sorry, you lost the game. The word was " + word + ".");
        alert("Sorry, you lost the game. The word was " + word + ".");
        restartGame();
      }
    }

    // Function to restart the game
    function restartGame() {
      // Randomly select a new word from the word list
      word = wordList[Math.floor(Math.random() * wordList.length)];
      // New everything
      correctGuesses = [];
      incorrectGuesses = [];
      document.getElementById("error").textContent = "";
      updateWord();
      updateRemainingGuesses();
      updateIncorrectGuesses();
    }

    updateWord();
  });

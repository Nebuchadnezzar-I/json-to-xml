# JSON Syntax Rules for Lexers

## 1. Whitespace Handling
- Whitespace (spaces, tabs, newlines) outside of tokens should be ignored. These include:
   - `Space` (`U+0020`)
   - `Tab` (`U+0009`)
   - `Line feed` (`U+000A`)
   - `Carriage return` (`U+000D`)

## 2. Object Syntax (`{}`)
- Objects are represented as key-value pairs enclosed in curly braces `{}`.
- Each key must be a string enclosed in double quotes.
- Key-value pairs are separated by a colon (`:`).
- Multiple pairs are separated by commas (`,`).

**Example:**
```json
{
    "key": "value",
    "key2": 123
}
```

### Edge Cases:
- An empty object is valid: `{}`.
- Trailing commas are **not allowed**: `{ "key": "value", }` is invalid.
- Keys must be strings enclosed in **double quotes**, not single quotes or bare words.

## 3. Array Syntax (`[]`)
- Arrays are lists of values enclosed in square brackets `[]`.
- Values are separated by commas (`,`).

**Example:**
```json
[1, "two", null, true]
```

### Edge Cases:
- An empty array is valid: `[]`.
- Trailing commas are **not allowed**: `[1, 2,]` is invalid.

## 4. String Syntax
- Strings are enclosed in **double quotes** (`"`).
- Strings can contain any Unicode character except control characters and unescaped quotes.
- Special characters must be escaped using backslashes (`\`):
   - `\"` (quote)
   - `\\` (backslash)
   - `\/` (slash)
   - `\b` (backspace)
   - `\f` (form feed)
   - `\n` (newline)
   - `\r` (carriage return)
   - `\t` (tab)
   - `\uXXXX` (unicode characters)

### Edge Cases:
- Escaped quotes inside strings are valid: `"He said \"hello\""` is valid.
- A string cannot contain unescaped quotes: `"abc"def"` is invalid.
- Control characters (`U+0000` through `U+001F`) are **not allowed** in strings and must be escaped.

## 5. Number Syntax
- Numbers can be integers or floats.
- They must not have leading zeroes (unless the number is `0`).
- Numbers can be negative, and they can include an optional exponent.

**Format:**
```
[ - ] (integer) [ . fraction ] [ e | E [ + | - ] exponent ]
```

 **Example:**
```json
123
-123
0.123
1.23e10
-1.23E-10
```

### Edge Cases:
- Leading zeros are **not allowed**: `0123` is invalid.
- Trailing decimals are **not allowed**: `123.` is invalid.
- The exponent part must be an integer: `1.23e10` is valid, but `1.23e1.5` is invalid.

## 6. Boolean Syntax
- Booleans are represented as `true` and `false` (lowercase).

**Example:**
```json
true
false
```

## 7. Null Syntax
- `null` is a valid literal representing a null value.

**Example:**
```json
null
```

## 8. Comma and Colon
- Commas are used to separate elements in arrays and objects.
- Colons are used to separate keys and values in objects.

### Edge Cases:
- Trailing commas are **not allowed**: `[1, 2,]` or `{"key": "value",}` is invalid.
- Missing commas between elements are invalid: `[1 2]` or `{"key1": "value1" "key2": "value2"}` is invalid.

## 9. EOF (End of File)
- The lexer should detect when the input ends unexpectedly, such as an open object `{` or array `[`.

**Example:**
```json
{"key": "value"
```

## 10. Character Limits
- String characters should conform to valid Unicode points.
- Numbers should not exceed valid JSON number ranges or use invalid characters.

## 11. Comments
- JSON **does not allow** comments. Lines like `// comment` or `/* comment */` are invalid.

## Full JSON Example
```json
{
    "name": "John Doe",
    "age": 30,
    "married": false,
    "children": null,
    "address": {
        "street": "1234 Elm St",
        "city": "Somewhere",
        "zip": "12345"
    },
    "favorites": [ "pizza", "ice cream", "cake" ]
}
```

## Key Points for the Lexer:
- Ignore whitespace between tokens.
- Tokenize keywords (`true`, `false`, `null`), punctuation (`{`, `}`, `[`, `]`, `:`, `,`), strings (with proper escaping), and numbers (with correct syntax).
- Handle invalid tokens (like unescaped quotes, misplaced commas, and numbers with leading zeroes).

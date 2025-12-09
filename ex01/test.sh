#!/bin/bash

# ==============================================================================
# Configuration
# ==============================================================================
# Le chemin vers votre programme RPN
RPN_PROGRAM="./RPN"
# Séparateur pour l'affichage
SEPARATOR="--------------------------------------------------"
# Compteur de tests
TEST_COUNT=0

# ==============================================================================
# Liste des expressions RPN à tester
# Les expressions 41 et 44 devraient normalement générer une erreur
# (Division par zéro ou erreur de syntaxe/pile)
# ==============================================================================
EXPRESSIONS=(
	"8 4 +"
	"9 3 -"
	"2 3 *"
	"6 3 /"
	"-5 3 +"
	"7 -2 *"
	"-8 -4 -"
	"1 9 3 / +"
	"-1 2 * 5 +"
	"4 5 1 - *"
	"0 9 / 2 +"
	"3 3 3 + -"
	"5 -1 / 4 +"
	"2 3 * 6 /"
	"9 3 / 2 *"
	"4 2 + 5 3 - *"
	"1 2 3 4 + + -"
	"5 2 3 * + 1 -"
	"9 3 2 / /"
	"3 3 * 9 / 1 +"
	"-1 -2 -3 + *"
	"6 -3 / 4 2 + *"
	"8 2 1 - / 4 +"
	"5 5 + 2 / 0 *"
	"7 1 - 3 3 * -"
	"1 2 3 4 5 * + - /"
	"9 3 / 3 / 3 /"
	"-9 3 / 2 - 1 +"
	"0 5 4 * + 1 -"
	"3 2 1 + * 6 -"
	"0 5 * 1 +"
	"4 -4 + 2 /"
	"1 3 * 6 / 2 +"
	"-2 2 * -8 /"
	"7 8 9 + -"
	"5 6 7 - * 8 +"
	"1 1 1 1 + + +"
	"-5 -4 * 2 / 1 -"
	"8 2 2 2 + + /"
	"3 5 * 2 1 + /"
	"1 2 - -3 * 9 +"
	"8 2 4 - /"
	"9 -3 - 2 * 10 -"
	"5 -6 7 + * 8 /"
	"-7 -1 / 2 - 3 *"
	"1 2 3 4 5 + * / +"
	"1 1 1 1 1 1 - - - - -"
	"2 3 * 4 + 5 6 - *"
	"9 3 * 2 1 + - 4 /"
)

INVALID_EXPRESSIONS=(
	"4 2 * +"     # Opérande manquant
	"1 2 3 +"     # Pile non vide à la fin
	"5 4 @"       # Caractère inconnu
	"--5 2 +"     # Format de nombre invalide
	"8 2 x"       # Opérateur inconnu
	"1 + 2"       # Format non RPN (Infixé)
	"3 3 + a"     # Caractère inconnu
	"5 !"         # Opérateur non supporté (unaire)
	""            # Input vide
	"9 8 7 6 +"     # Pile non vide (multiple)
	"5 * * 3"     # Trop d'opérateurs consécutifs
	"4 0 /"       # Division par zéro
	"6 3 - -"     # Opérande manquant
	"22 3 +"      # Nombre à double chiffre (si limité)
	"3 4 + /"     # Opérande manquant
	"5 -2 * -"    # Opérande manquant
	"4 5 #"       # Caractère inconnu
	"1 2 3"       # Pile non vide (opérations manquantes)
	"(1 2 +)"     # Parenthèses (invalide en RPN)
)

# ==============================================================================
# Fonction principale de test
# ==============================================================================
echo "Démarrage des tests RPN. Programme: ${RPN_PROGRAM}"
echo "${SEPARATOR}"

# Vérifie si le programme existe et est exécutable
if [ ! -x "$RPN_PROGRAM" ]; then
	echo "ERREUR: Le programme RPN ('$RPN_PROGRAM') n'existe pas ou n'est pas exécutable."
	exit 1
fi

for expression in "${EXPRESSIONS[@]}"; do
	TEST_COUNT=$((TEST_COUNT + 1))

	echo "TEST #${TEST_COUNT}"
	echo "  Input: \"${expression}\""

	# Exécution du programme et capture de la sortie
	# L'exécution est lancée avec la commande demandée : ./RPN "${expression}"
	OUTPUT=$(${RPN_PROGRAM} "${expression}" 2>&1)
	EXIT_CODE=$?

	echo "  Output: ${OUTPUT}"

	# Vérifie le code de retour pour indiquer le succès ou l'échec
	if [ $EXIT_CODE -eq 0 ]; then
		echo "  Status: Succès (Code 0)"
	else
		echo "  Status: Échec/Erreur Programme (Code $EXIT_CODE)"
	fi

	echo "${SEPARATOR}"
done

echo
echo "--- Démarrage des tests INVALIDES ---"

for expression in "${INVALID_EXPRESSIONS[@]}"; do
	TEST_COUNT=$((TEST_COUNT + 1))
	echo "Test: \"${expression}\""

	# Exécution de votre programme
	# La sortie est dirigée vers /dev/null pour ne pas encombrer,
	# car on s'attend juste à un code d'erreur non-zéro.
	${RPN_PROGRAM} "${expression}" > /dev/null 2>&1
	EXIT_CODE=$?

	if [ $EXIT_CODE -ne 0 ]; then
		echo "  ✔️ PASS: Le programme a retourné le code d'erreur $EXIT_CODE."
	else
		echo "  ❌ FAIL: Le programme a retourné le code 0 (Succès) pour une entrée invalide."
	fi
	echo "---"
done

echo "Tests terminés. ${TEST_COUNT} expressions exécutées."

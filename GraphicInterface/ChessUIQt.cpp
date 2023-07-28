#include "ChessUIQt.h"
#include "ChessUIQt.h"

#include <QInputDialog>
#include <QMessageBox>

#include "IChessGame.h"
#include "ChessException.h"

#include <QClipboard>
#include <QGuiApplication>

#include <QLabel>
#include <QPalette>

static EType ToETypeFromQString(const QString& s)
{
    if (s == "Rook")
    {
        return EType::Rook;
    } 
    else if (s == "Bishop")
    {
        return EType::Bishop;
    }
    else if (s == "Queen")
    {
        return EType::Queen;
    }
    else
    {
        return EType::Horse;
    }
}

static PieceType ToPieceTypeFromEType(const EType t)
{
    switch (t)
    {
    case EType::Rook:
        return PieceType::rook;
    case EType::Horse:
        return PieceType::knight;
    case EType::King:
        return PieceType::king;
    case EType::Queen:
        return PieceType::queen;
    case EType::Bishop:
        return PieceType::bishop;
    case EType::Pawn:
        return PieceType::pawn;
	default:
        return PieceType::none;
    }
}

ChessUIQt::ChessUIQt(QWidget *parent)
    : QMainWindow(parent)
{
    //Widget containing everything
    QWidget* mainWidget = new QWidget();
    QGridLayout* mainGridLayout = new QGridLayout();
    
    InitializeBoard(mainGridLayout);
    InitializeMessage(mainGridLayout);
    InitializeButtons(mainGridLayout);
    InitializeTimers(mainGridLayout);
    InitializeHistory(mainGridLayout);
	InitializeCapturedBoxes(mainGridLayout);

    mainWidget->setLayout(mainGridLayout);
    this->setCentralWidget(mainWidget);

	QPalette palette = this->palette();
    palette.setColor(QPalette::Window, QColor("#F2D8D8"));
	this->setPalette(palette);
}

ChessUIQt::~ChessUIQt()
{
    //No delete?
    //https://doc.qt.io/qt-6/objecttrees.html
}

void ChessUIQt::SetGame(IChessGame* game)
{
    m_game = game;
}

void ChessUIQt::InitializeMessage(QGridLayout * mainGridLayout)
{
    m_MessageLabel = new QLabel();
    m_MessageLabel->setText("Waiting for white player\n");
    m_MessageLabel->setAlignment(Qt::AlignCenter);
    m_MessageLabel->setStyleSheet("font-size: 20px; font-weight: bold;");

    mainGridLayout->addWidget(m_MessageLabel, 0, 1, 1, 3);
}

void ChessUIQt::InitializeButtons(QGridLayout* mainGridLayout)
{
    QPushButton* saveButton = new QPushButton("Save");
    QPushButton* loadButton = new QPushButton("Load");
    QPushButton* restartButton = new QPushButton("Restart");
    QPushButton* drawButton = new QPushButton("Draw");
    QPushButton* saveClipboardButton = new QPushButton("Save in Clipboard");

    QWidget* buttonContainer = new QWidget();
    QGridLayout* btnGrid = new QGridLayout();

    btnGrid->addWidget(saveButton, 0, 0);
    btnGrid->addWidget(loadButton, 0, 1);
    btnGrid->addWidget(restartButton, 0, 2);
    btnGrid->addWidget(drawButton, 0, 3);
    btnGrid->addWidget(saveClipboardButton, 0, 4);

    connect(saveButton, &QPushButton::pressed, this, &ChessUIQt::OnSaveButtonClicked);
    connect(loadButton, &QPushButton::pressed, this, &ChessUIQt::OnLoadButtonClicked);
    connect(restartButton, &QPushButton::pressed, this, &ChessUIQt::OnRestartButtonClicked);
    connect(drawButton, &QPushButton::pressed, this, &ChessUIQt::OnDrawButtonClicked);
    connect(saveClipboardButton, &QPushButton::pressed, this, &ChessUIQt::OnSaveInClipboardButtonClicked);

    buttonContainer->setLayout(btnGrid);
    mainGridLayout->addWidget(buttonContainer, 0, 0, 1, 1);
}

void ChessUIQt::InitializeTimers(QGridLayout* mainGridLayout)
{
    QWidget* timerContainer = new QWidget();
    QGridLayout* timerGrid = new QGridLayout();

    QLabel* blackTimerLbl = new QLabel("Black timer: ");
    m_BlackTimer = new QLabel("00:00:00");

    QPushButton* pauseTimerBtn = new QPushButton(" Pause | Resume");
    //TODO Create slot and connect button

    QLabel* whiteTimerLbl = new QLabel("    White timer: ");
    m_WhiteTimer = new QLabel("00:00:00");

    timerContainer->setFixedWidth(400);

    timerGrid->addWidget(blackTimerLbl, 0, 0);
    timerGrid->addWidget(m_BlackTimer, 0, 1);
    timerGrid->addWidget(pauseTimerBtn, 0, 2);
    timerGrid->addWidget(whiteTimerLbl, 0, 3);
    timerGrid->addWidget(m_WhiteTimer, 0, 4);

    timerContainer->setLayout(timerGrid);
    mainGridLayout->addWidget(timerContainer, 2, 0, 1, 4, Qt::AlignCenter);
}

void ChessUIQt::InitializeHistory(QGridLayout* mainGridLayout)
{
    m_MovesList = new QListWidget();
    m_MovesList->setMinimumWidth(350);
    m_MovesList->setMaximumWidth(450);
    connect(m_MovesList, &QListWidget::itemActivated, this, &ChessUIQt::OnHistoryClicked);
    mainGridLayout->addWidget(m_MovesList, 1, 0, 1, 1);
}

#include <QLabel> // Include the QLabel header

void ChessUIQt::InitializeBoard(QGridLayout* mainGridLayout)
{
	QGridLayout* chessGridLayout;
	chessGridLayout = new QGridLayout();
	QWidget* board = new QWidget();

	for (int i = 0; i < 8; i++)
	{
		QLabel* rowLabel = new QLabel(QString::number(8 - i) + "  ");
		rowLabel->setAlignment(Qt::AlignCenter);
		chessGridLayout->addWidget(rowLabel, i, 0);

		QFont rowFont = rowLabel->font();
		rowFont.setPointSize(10);
		rowLabel->setFont(rowFont);

		QPalette rowPalette = rowLabel->palette();
		rowPalette.setColor(QPalette::WindowText, QColor("#84A7A1"));
		rowLabel->setPalette(rowPalette);

		for (int j = 0; j < 8; j++)
		{
			m_grid[i][j] = new GridButton({ i,j }, PieceType::none, PieceColor::none);
			chessGridLayout->addWidget(m_grid[i][j], i, j + 1);
			chessGridLayout->setSpacing(2.5);
			connect(m_grid[i][j], &GridButton::Clicked, this, &ChessUIQt::OnButtonClicked);
		}
	}

	for (int j = 0; j < 8; j++)
	{
		QLabel* colLabel = new QLabel(QString(QChar('A' + j)));
		colLabel->setAlignment(Qt::AlignCenter);
		chessGridLayout->addWidget(colLabel, 8, j + 1);

        QFont colFont = colLabel->font();
        colFont.setPointSize(10);
        colLabel->setFont(colFont);

		QPalette colPalette = colLabel->palette();
		colPalette.setColor(QPalette::WindowText, QColor("#84A7A1"));
		colLabel->setPalette(colPalette);
	}

	board->setLayout(chessGridLayout);
	mainGridLayout->addWidget(board, 1, 2, 1, 1);
}

void ChessUIQt::InitializeCapturedBoxes(QGridLayout* mainGridLayout)
{
	QGridLayout* capturedGrid1;
	capturedGrid1 = new QGridLayout();
	QWidget* captured1 = new QWidget();

	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			m_capturedGrid[i][j] = new GridButton({ j,i }, PieceType::none, PieceColor::none);
			m_capturedGrid[i][j]->setStyleSheet("background-color: #d6c4b8; border: none;");
			capturedGrid1->addWidget(m_capturedGrid[i][j], j, i);
			capturedGrid1->setSpacing(0);
		}
	}

	captured1->setLayout(capturedGrid1);
	mainGridLayout->addWidget(captured1, 1, 1, 1, 1);

	QGridLayout* capturedGrid2;
	capturedGrid2 = new QGridLayout();
	QWidget* captured2 = new QWidget();

	for (int i = 2; i < 4; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			m_capturedGrid[i][j] = new GridButton({ j,i }, PieceType::none, PieceColor::none);
			m_capturedGrid[i][j]->setStyleSheet("background-color: #d6c4b8; border: none;");
			capturedGrid2->addWidget(m_capturedGrid[i][j], j, i);
			capturedGrid2->setSpacing(0);
		}
	}

	captured2->setLayout(capturedGrid2);
	mainGridLayout->addWidget(captured2, 1, 3, 1, 1);
}


void ChessUIQt::OnButtonClicked(const Position& position)
{
	//At second click
	if (m_selectedCell.has_value())
	{
		if (m_selectedCell.value() == position)
		{
			m_grid[m_selectedCell.value().row][m_selectedCell.value().col]->setSelected(false);
			m_selectedCell.reset();
			UnhighlightPossibleMoves(m_game->GetPossibleMoves(position));
		}
		else
		{
			//TODO COMPLETE ME...
			try
			{
				UnhighlightPossibleMoves(m_game->GetPossibleMoves(m_selectedCell.value()));
				m_game->MakeMove(m_selectedCell.value(), position);
			}
			catch (const OccupiedByOwnPieceException& e)
			{
				UnhighlightPossibleMoves(m_game->GetPossibleMoves(m_selectedCell.value()));

				m_grid[m_selectedCell.value().row][m_selectedCell.value().col]->setSelected(false);
				m_selectedCell.reset();

				m_selectedCell = position;
				m_grid[position.row][position.col]->setSelected(true);

				AppendThrowMessage("");
				HighlightPossibleMoves(m_game->GetPossibleMoves(m_selectedCell.value()));

				return;
			}
			catch (const ChessException& e)
			{
				HighlightPossibleMoves(m_game->GetPossibleMoves(m_selectedCell.value()));
				AppendThrowMessage(e.what());
				return;
			}

			//Unselect prev. pressed button
			m_grid[m_selectedCell.value().row][m_selectedCell.value().col]->setSelected(false);
			m_selectedCell.reset();
		}
	}
	//At first click
	else
	{
		m_selectedCell = position;
		m_grid[position.row][position.col]->setSelected(true);

		//TODO Show possible moves here
		HighlightPossibleMoves(m_game->GetPossibleMoves(position));
	}
}

void ChessUIQt::OnSaveButtonClicked()
{
    //TODO ...

}

void ChessUIQt::OnLoadButtonClicked()
{
    //TODO ...
}

void ChessUIQt::OnRestartButtonClicked()
{
	QMessageBox::StandardButton reply;
	reply = QMessageBox::question(this, "Restart", "All progress will be lost. Are you sure?", QMessageBox::Yes | QMessageBox::No);

	if (reply == QMessageBox::Yes)
	{
        m_game->ResetGame();
	}
}

void ChessUIQt::OnDrawButtonClicked()
{
    //TODO MODIFY ME
    m_game->RequestDraw();

    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Draw proposal", "Do you accept a draw?", QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes) 
    {
		m_game->AcceptDrawProposal();
		m_MessageLabel->setText("Game over!\nDraw.");
		QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "Game Over", "Draw.\nDo you want to play again?", QMessageBox::Yes | QMessageBox::Close);
		
		if (reply == QMessageBox::Yes)
		{
            m_game->ResetGame();
		}
		else
		{
			Exit();
		}
    }
    else
    {
        m_game->DeclineDrawProposal();
    }
}

void ChessUIQt::OnSaveInClipboardButtonClicked()
{
    QString textToCopy;

    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            PieceType type = m_grid[i][j]->GetType();
            PieceColor color = m_grid[i][j]->GetColor();

            char piece;

			switch (type) {
			case PieceType::none:
                piece = ' ';
				break;
			case PieceType::king:
                piece = 'k';
				break;
			case PieceType::rook:
                piece = 'r';
				break;
			case PieceType::bishop:
                piece = 'b';
				break;
			case PieceType::queen:
                piece = 'q';
				break;
			case PieceType::knight:
                piece = 'h';
				break;
			case PieceType::pawn:
                piece = 'p';
				break;
			default:
                piece = '*';
				break;
			}

            if (color == PieceColor::black)
                piece = std::toupper(piece);   // include to upper if it doesn t work //

            textToCopy.append("\'");
            textToCopy.append(piece);
            textToCopy.append("\', ");
        }
        textToCopy.append("\n");
    }
    textToCopy.chop(3);
    
    QClipboard* clipboard = QGuiApplication::clipboard();
    clipboard->setText(textToCopy);
}

void ChessUIQt::OnHistoryClicked(QListWidgetItem* item)
{
    int index = m_MovesList->currentRow();
    
    //TODO ...
}

void ChessUIQt::UpdateHistory()
{
    m_MovesList->clear();

    //TODO modify me...
    int numMoves = 10;
    for (int i = 0; i < numMoves; i++) {
        m_MovesList->addItem("#1   Color: Black   Move: A1 A2");
    }
}

void ChessUIQt::UpdateBoard()
{
    for (int i = 0; i < 8; i++) 
    {
        for (int j = 0; j < 8; j++) 
        {
            std::pair<PieceType, PieceColor> newPiece;

            if (m_game->GetIPiecePtr(Position(i,j)))
            {
				switch (m_game->GetIPiecePtr(Position(i, j))->GetType())
				{
				case EType::Rook:
					newPiece.first = PieceType::rook;
					break;
				case EType::Horse:
					newPiece.first = PieceType::knight;
					break;
				case EType::Bishop:
					newPiece.first = PieceType::bishop;
					break;
				case EType::Queen:
					newPiece.first = PieceType::queen;
					break;
				case EType::King:
					newPiece.first = PieceType::king;
					break;
				case EType::Pawn:
					newPiece.first = PieceType::pawn;
					break;
				default:
					break;
				}

                switch (m_game->GetIPiecePtr(Position(i, j))->GetColor())
				{
				case EColor::Black:
					newPiece.second = PieceColor::black;
					break;
				case EColor::White:
					newPiece.second = PieceColor::white;
					break;
				default:
					break;
				}
            }
            else
            {
                newPiece.first = PieceType::none;
				newPiece.second = PieceColor::none;
            }
            
            m_grid[i][j]->setPiece(newPiece);
			m_grid[i][j]->setSelected(false);
			m_grid[i][j]->setHighlighted(false);
        }
    }

}

void ChessUIQt::UpdateCaptures()
{
	IPieceList capturedByWhite = m_game->GetCapturedPieces(EColor::Black);

	auto it = capturedByWhite.begin();

	for (int i = 0; i < 2 && it != capturedByWhite.end(); i++)
	{
		for (int j = 0; j < 8 && it != capturedByWhite.end(); j++)
		{
			std::pair<PieceType, PieceColor> newPiece;

			switch ((*it)->GetType())
			{
			case EType::Rook:
				newPiece.first = PieceType::rook;
				break;
			case EType::Horse:
				newPiece.first = PieceType::knight;
				break;
			case EType::Bishop:
				newPiece.first = PieceType::bishop;
				break;
			case EType::Queen:
				newPiece.first = PieceType::queen;
				break;
			case EType::King:
				newPiece.first = PieceType::king;
				break;
			case EType::Pawn:
				newPiece.first = PieceType::pawn;
				break;
			default:
				break;
			}

			switch ((*it)->GetColor())
			{
			case EColor::Black:
				newPiece.second = PieceColor::black;
				break;
			case EColor::White:
				newPiece.second = PieceColor::white;
				break;
			default:
				break;
			}

			m_capturedGrid[i][j]->setPiece(newPiece);
			m_capturedGrid[i][j]->setSelected(false);
			m_capturedGrid[i][j]->setHighlighted(false);
			m_capturedGrid[i][j]->setStyleSheet("background-color: #d6c4b8; border: none;");

			it++;
		}
	}

	IPieceList capturedByBlack = m_game->GetCapturedPieces(EColor::White);

	it = capturedByBlack.begin();

	for (int i = 2; i < 4 && it != capturedByBlack.end(); i++)
	{
		for (int j = 0; j < 8 && it != capturedByBlack.end(); j++)
		{
			std::pair<PieceType, PieceColor> newPiece;

			switch ((*it)->GetType())
			{
			case EType::Rook:
				newPiece.first = PieceType::rook;
				break;
			case EType::Horse:
				newPiece.first = PieceType::knight;
				break;
			case EType::Bishop:
				newPiece.first = PieceType::bishop;
				break;
			case EType::Queen:
				newPiece.first = PieceType::queen;
				break;
			case EType::King:
				newPiece.first = PieceType::king;
				break;
			case EType::Pawn:
				newPiece.first = PieceType::pawn;
				break;
			default:
				break;
			}

			switch ((*it)->GetColor())
			{
			case EColor::Black:
				newPiece.second = PieceColor::black;
				break;
			case EColor::White:
				newPiece.second = PieceColor::white;
				break;
			default:
				break;
			}

			m_capturedGrid[i][j]->setPiece(newPiece);
			m_capturedGrid[i][j]->setSelected(false);
			m_capturedGrid[i][j]->setHighlighted(false);
			m_capturedGrid[i][j]->setStyleSheet("background-color: #d6c4b8; border: none;");

			it++;
		}
	}
}

void ChessUIQt::HighlightPossibleMoves(const PositionList& possibleMoves)
{
    for (const auto& position : possibleMoves) 
    {
        if (m_game->GetIPiecePtr(position))
        {
            m_grid[position.row][position.col]->setHighlighted(2);
        } 
        else  m_grid[position.row][position.col]->setHighlighted(1);
    }
}

void ChessUIQt::UnhighlightPossibleMoves(const PositionList& possibleMoves)
{
	for (const auto& position : possibleMoves) {
		m_grid[position.row][position.col]->setHighlighted(false);
	}
}

void ChessUIQt::StartGame()
{
    //TODO MODIFY ME OR DELETE ME
    UpdateBoard();
}

QString ChessUIQt::ShowPromoteOptions()
{
    QInputDialog dialog;
    QList<QString> options;
    options.append("Rook");
    options.append("Bishop");
    options.append("Queen");
    options.append("Knight");

    dialog.setComboBoxItems(options);
    dialog.setModal(true);

    bool ok;
    QString item = QInputDialog::getItem(this, tr("Pawn promote"),
        tr("Promote pawn to: "), options, 0, false, &ok);

    if (ok && !item.isEmpty())
    {
        //TODO
        return item;
        //game.promotePawn(parseQStringToPieceType(item))

        ////TODO DELETE ME...
        //QMessageBox notification;
        //notification.setText("You selected " + item);
        //notification.exec();
    }
    return QString();
}

void ChessUIQt::UpdateMessage(const QString& message)
{
    m_MessageLabel->setText(message + '\n');
}

void ChessUIQt::AppendThrowMessage(const QString& message)
{
	QString s = m_MessageLabel->text();
	for (auto it = s.begin(); it != s.end(); it++)
	{
		if (*it == '\n')
		{
			s.erase(it, s.end());
			break;
		}
	}
	s.append('\n');
	s.append(message);
	m_MessageLabel->setText(s);
}

void ChessUIQt::OnMoveMade(Position init, Position fin)
{
    std::pair<PieceType, PieceColor> initPosPiece;
    initPosPiece.first = m_grid[init.row][init.col]->GetType();
    initPosPiece.second = m_grid[init.row][init.col]->GetColor();

	m_grid[fin.row][fin.col]->setPiece(initPosPiece);
    //m_grid[fin.row][fin.col]->setSelected(false);
    //m_grid[fin.row][fin.col]->setHighlighted(false);

    std::pair<PieceType, PieceColor> voidPiece;
    voidPiece.first = PieceType::none;
    voidPiece.second = PieceColor::none;

    m_grid[init.row][init.col]->setPiece(voidPiece);

	//UpdateBoard();

	switch (m_game->GetCurrentPlayer())
	{
	case EColor::Black:
		UpdateMessage("Waiting for black player");
		break;
	case EColor::White:
		UpdateMessage("Waiting for white player");
		break;
	default:
		break;
	}

	UpdateCaptures();
}

void ChessUIQt::OnGameOver(EGameResult result)
{
	if (m_game->IsDraw())
	{
		m_MessageLabel->setText("Game over!\nDraw.");
		QMessageBox::StandardButton reply;
		reply = QMessageBox::question(this, "Game Over", "Draw.\nDo you want to play again?", QMessageBox::Yes | QMessageBox::Close);

		if (reply == QMessageBox::Yes)
		{
            m_game->ResetGame();
		}
		else
		{
			Exit();
		}
		return;
	}
	
    //m_MessageLabel->setText("Game over!\nBlack player won");
	QMessageBox::StandardButton reply;

	if (m_game->IsWonByBlackPlayer())
	{
        m_MessageLabel->setText("Game over!\nBlack player won");
		reply = QMessageBox::question(this, "Game Over", "Black player won.\nDo you want to play again?", QMessageBox::Yes | QMessageBox::Close);
	}
	if (m_game->IsWonByWhitePlayer())
	{
        m_MessageLabel->setText("Game over!\nWhite player won");
		reply = QMessageBox::question(this, "Game Over", "White player won.\nDo you want to play again?", QMessageBox::Yes | QMessageBox::Close);
	}

	if (reply == QMessageBox::Yes)
	{
        m_game->ResetGame();
	}
	else
	{
		Exit();
	}
}

void ChessUIQt::OnPawnUpgrade(Position pos)
{
    QString item = ShowPromoteOptions();

    EType upgradeType = ToETypeFromQString(item);

    m_game->UpgradePawn(upgradeType);

	std::pair<PieceType, PieceColor> upgradePiece;
    if (pos.row == 0)
    {
        upgradePiece.second = PieceColor::white;
    }
    else
    {
        upgradePiece.second = PieceColor::black;
    }
    upgradePiece.first = ToPieceTypeFromEType(upgradeType);

	m_grid[pos.row][pos.col]->setPiece(upgradePiece);

	/*switch (m_game->GetCurrentPlayer())
	{
	case EColor::Black:
		UpdateMessage("Waiting for black player");
		break;
	case EColor::White:
		UpdateMessage("Waiting for white player");
		break;
	default:
		break;
	}*/
}

void ChessUIQt::OnCheck()
{
	QString s = m_MessageLabel->text();
    s.remove(s.size() - 1, 1);
    s.append(" - ");
	s.append("Solve check\n");
	m_MessageLabel->setText(s);
    //AppendThrowMessage("Solve check state");
    //UpdateBoard();
}

void ChessUIQt::OnGameRestarted()
{
    //Widget containing everything
    QWidget* mainWidget = new QWidget();
    QGridLayout* mainGridLayout = new QGridLayout();

    InitializeBoard(mainGridLayout);
    InitializeMessage(mainGridLayout);
    InitializeButtons(mainGridLayout);
    InitializeTimers(mainGridLayout);
    InitializeHistory(mainGridLayout);
	InitializeCapturedBoxes(mainGridLayout);

    mainWidget->setLayout(mainGridLayout);
    this->setCentralWidget(mainWidget);

    StartGame();
}

